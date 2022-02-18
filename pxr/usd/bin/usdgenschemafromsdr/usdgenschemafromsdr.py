#!/pxrpythonsubst
#
# Copyright 2021 Pixar
#
# Licensed under the Apache License, Version 2.0 (the "Apache License")
# with the following modification; you may not use this file except in
# compliance with the Apache License and the following modification to it:
# Section 6. Trademarks. is deleted and replaced with:
#
# 6. Trademarks. This License does not grant permission to use the trade
#    names, trademarks, service marks, or product names of the Licensor
#    and its affiliates, except as required to comply with Section 4(c) of
#    the License and to reproduce the content of the NOTICE file.
#
# You may obtain a copy of the Apache License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the Apache License with the above modification is
# distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the Apache License for the specific
# language governing permissions and limitations under the Apache License.
#
"""
This script generates dynamic schema.usda, generatedSchema.usda and
plugInfo.json. The schema.usda is generated by parsing appropriate sdrNodes 
provided in a config file. Along with providing sdrNodes types and identifier, 
the config file also provides a list of subLayers which the auto populated 
schema.usda should sublayer. Code generation can also be optionally enabled via 
the json config. Note that code generation is disabled by default.

The script takes 3 arguments:
    - a json config, providing sourceType and sdrNodeIdentifiers
    - a destination directory. Note that a schema.usda with appropriate GLOBAL
      prim providing a libraryName in its customData, must be present at this
      location. This is also the location where generatedSchema.usda,
      plugInfo.json will get exported.
      In the case code generation is explicitly enabled in the config, 
      libraryPath must also be provided along with libraryName in the 
      customData, else usdGenSchema will fail.
    - an optional noreadme to ignore generating a README.md providing brief 
      explaination of the contents of the directory.

This script will run usdGenSchema on the auto populated schema.usda.
"""

from argparse import ArgumentParser, RawTextHelpFormatter
from textwrap import dedent
import os, sys, json
from subprocess import call
from pxr import Sdf, Tf, UsdUtils, Sdr
from pxr.UsdUtils.constantsGroup import ConstantsGroup

class SchemaConfigConstants(ConstantsGroup):
    SDR_NODES = "sdrNodes"
    SOURCE_ASSET_NODES = "sourceAssetNodes"
    SUBLAYERS_STRING = "sublayers"
    RENDER_CONTEXT = "renderContext"

class SchemaLayerConstants(ConstantsGroup):
    GLOBAL_PRIM_PATH = "/GLOBAL"
    LIBRARY_NAME_STRING = "libraryName"
    SKIP_CODE_GENERATION = "skipCodeGeneration"
    SCHEMA_PATH_STRING = "schema.usda"

class MiscConstants(ConstantsGroup):
    USD_GEN_SCHEMA = "usdGenSchema"
    WINDOWS = "Windows"
    PATH = "PATH"
    CMD_EXTENSION = ".cmd"
    README_FILE_NAME = "README.md"

def _GetUsdGenSchemaCmd():
    # Adopting logic from usddiff.py
    from distutils.spawn import find_executable
    import platform

    cmd = find_executable(MiscConstants.USD_GEN_SCHEMA)
    
    # usdGenSchema is found in PATH
    if cmd:
        return cmd
    else:
        # try to find usdGenSchema from installed directory of this script
        cmd = find_executable(USD_GEN_SCHEMA, 
                path=os.path.abspath(os.path.dirname(sys.argv[0])))
        if cmd:
            return cmd

    if (platform.system() == 'Windows'):
        # find_executable under Windows only returns *.EXE files
        # so we need to traverse PATH.
        for path in os.environ['PATH'].split(os.pathsep):
            base = os.path.join(path, USD_GEN_SCHEMA)
            # We need to test for usdGenSchema.cmd first because on Windows, 
            # the USD executables are wrapped due to lack of N*IX style shebang 
            # support on Windows.
            for ext in [MiscConstants.CMD_EXTENSION, '']:
                cmd = base + ext
                if os.access(cmd, os.X_OK):
                    return cmd
    return None

def _ConfigureSchemaLayer(schemaLayer, schemaSubLayers, skipCodeGeneration):
    # - add sublayers
    subLayers = schemaLayer.subLayerPaths
    subLayersList = list(subLayers)
    subLayersList.extend(schemaSubLayers)
    schemaLayer.subLayerPaths = list(set(subLayersList))

    globalPrim = schemaLayer.GetPrimAtPath(
            SchemaLayerConstants.GLOBAL_PRIM_PATH)
    if not globalPrim:
        Tf.RaiseRuntimeError("Missing %s prim in schema.usda." \
                %(SchemaLayerConstants.GLOBAL_PRIM_PATH))

    if not globalPrim.customData:
        Tf.RaiseRuntimeError("customData must be defined on the %s prim" \
                %(SchemaLayerConstants.GLOBAL_PRIM_PATH))

    customDataDict = dict(globalPrim.customData)
    if SchemaLayerConstants.LIBRARY_NAME_STRING not in customDataDict:
        Tf.RaiseRuntimeError("customData on %s prim must provide a " \
            "%s." %(SchemaLayerConstants.GLOBAL_PRIM_PATH, 
                SchemaLayerConstants.LIBRARY_NAME_STRING))
    customDataDict[SchemaLayerConstants.SKIP_CODE_GENERATION] = \
            skipCodeGeneration
    globalPrim.customData = customDataDict

    schemaLayer.Save()


if __name__ == '__main__':
    # Parse command line

    # config file provides:
    parser = ArgumentParser(description='''
    This script generates dynamic schema.usda, generatedSchema.usda and
    plugInfo.json. The schema.usda is generated by parsing appropriate sdrNodes 
    provided in a config file. Along with providing sdrNodes types and 
    identifier, the config file also provides a list of subLayers which the auto 
    populated schema.usda should sublayer. Code generation can also be 
    optionally enabled via the json config, note that code generation is 
    disabled by default.

    The script takes 3 arguments:
        - a json config, providing sdrNodes via sourceType, sdrNodeIdentifiers
          or explicit list of absolute asset file paths (sourceAssetNodes) and 
          a list of sublayers.
        - a destination directory. Note that a schema.usda with appropriate 
          GLOBAL prim providing a libraryName in its customData, must be 
          present at this location. This is also the location where 
          generatedSchema.usda, plugInfo.json will get exported.
          In the case code generation is explicitly enabled in the config, 
          libraryPath must also be provided along with libraryName in the 
          customData, else usdGenSchema will fail.
        - an optional noreadme to ignore generating a README.md providing brief 
          explaination of the contents of the directory.

    This script will run usdGenSchema on the auto populated schema.usda.
    
    The schema.usda populated specifications from the provided sdrNodes using
    UsdUtils.UpdateSchemaWithSdrNode and skipCodeGeneration metadata will be 
    set to true, unless explicitly marked False in the config for this 
    schema.usda.

    UsdUtils.UpdateSchemaWithSdrNode is responsible for:
    %s
    ''' %(UsdUtils.UpdateSchemaWithSdrNode.__doc__), 
    formatter_class=RawTextHelpFormatter)
    parser.add_argument('schemaConfig',
            nargs='?',
            type=str,
            default='./schemaConfig.json',
            help=dedent('''
            A json config providing sdrNodes via sourceType, sdrNodeIdentifiers
            or explicit list of absolute asset file paths (sourceAssetNodes).
            Note that for nodes specified under sourceAssetNodes we will use 
            the basename stripped of extension as the shaderId for nodes we 
            create.
            And also optionally providing a list of sublayers which the 
            schema.usda will sublayer. Code generation can also be optionally 
            enabled via the json config, note that code generation is disabled 
            by default. [Default: %(default)s]').
            Example json config file:
                {
                        "sdrNodes": 
                        {
                            "renderContext": "myRenderContext",
                            "sourceType": [
                                "sdrIdentifier1",
                                "sdrIdentifier2",
                                "sdrIdentifier3"
                            ],
                            "sourceAssetNodes": [
                                "/absolutepath/to/sdrNodeIdentifyingAsset1.extension,
                                "/absolutepath/to/sdrNodeIdentifyingAsset1.extension,
                            ],
                        },
                        "sublayers": [
                            "usd/schema.usda", 
                            "usdGeom/schema.usda", 
                            "usdLux/schema.usda"
                            ],
                        "skipCodeGeneration": True
                }
            '''))
    parser.add_argument('schemaGenerationPath',
            nargs='?',
            type=str,
            default='.',
            help=dedent('''
            The target directory where the code should be generated. The script
            assumes a basic schema.usda is defined at this location with a 
            GLOBAL prim configured with appropriate libraryName.
            [Default: %(default)s]
            '''))
    parser.add_argument('--noreadme',
            default=False,
            action='store_true',
            help=dedent('''
            When specified a README.md will not be created in the schemaGenerationPath
            explaining the source of the contents of this directory.
            '''))
    parser.add_argument('-v', '--validate',
            action='store_true',
            help=dedent('''
            This is passed to usdGenSchem to verify that the source files are 
            unchanged.
            '''))

    args = parser.parse_args()
    schemaGenerationPath = os.path.abspath(args.schemaGenerationPath)
    schemaConfig = os.path.abspath(args.schemaConfig)
    writeReadme = not args.noreadme
    validate = args.validate

    if not os.path.isfile(schemaConfig):
        Tf.RaiseRuntimeError("(%s) json config does not exist" %(schemaConfig))

    # Parse json config to extract sdrNodes and schema sublayers
    try:
        with open(schemaConfig) as json_file:
            config = json.load(json_file)
    except ValueError as ve:
        Tf.RaiseRuntimeError("Error loading (%s), value error: (%s)" \
                %(schemaConfig, ve))

    if not isinstance(config, dict):
        Tf.Warn("Invalid json config provided, expecting a dictionary")
        sys.exit(1)

    # Note that for nodes with explicit asset paths, this list stores a tuple,
    # with first entry being the sdrNode and second the true identifier
    # (identified from the file basename, which should match the node identifier
    # when queries using GetShaderNodeByIdentifierAndType at runtime).
    sdrNodesToParse = []
    renderContext = ""

    sdrNodesDict = config.get(SchemaConfigConstants.SDR_NODES)
    if sdrNodesDict:
        # Extract any renderContext from the config if specified.
        if SchemaConfigConstants.RENDER_CONTEXT in sdrNodesDict.keys():
            renderContext = \
                    sdrNodesDict.get(SchemaConfigConstants.RENDER_CONTEXT)

        # Extract sdrNodes from the config
        sdrRegistry = Sdr.Registry()
        for sourceType in sdrNodesDict.keys():
            if sourceType == SchemaConfigConstants.RENDER_CONTEXT:
                continue
            if sourceType == SchemaConfigConstants.SOURCE_ASSET_NODES:
                # process sdrNodes provided by explicit sourceAssetNodes
                for assetPath in \
                    sdrNodesDict.get(SchemaConfigConstants.SOURCE_ASSET_NODES):
                    node = Sdr.Registry().GetShaderNodeFromAsset(assetPath)
                    nodeIdentifier = \
                        os.path.splitext(os.path.basename(assetPath))[0]
                    if node:
                        sdrNodesToParse.append((node, nodeIdentifier))
                    else:
                        Tf.Warn("Node not found at path: %s." %(assetPath))
                continue
            for nodeId in sdrNodesDict.get(sourceType):
                node = sdrRegistry.GetShaderNodeByIdentifierAndType(nodeId,
                        sourceType)
                if node is not None:
                    # This is a workaround to iterate through invalid sdrNodes 
                    # (nodes not having any input or output properties). 
                    # Currently these nodes return false when queried for 
                    # IsValid().
                    # Refer: pxr/usd/ndr/node.h#140-149
                    sdrNodesToParse.append(node)
                else:
                    Tf.Warn("Invalid Node (%s:%s) provided." %(sourceType,
                        nodeId))
    else:
        Tf.Warn("No sdr nodes provided to generate a schema.usda")
        sys.exit(1)

    if not sdrNodesToParse:
        Tf.Warn("No valid sdr nodes provided to generate a schema.usda")
        sys.exit(1)

    schemaSubLayers = config.get(SchemaConfigConstants.SUBLAYERS_STRING, [])

    schemaLayerPath = os.path.join(schemaGenerationPath, 
            SchemaLayerConstants.SCHEMA_PATH_STRING)
    schemaLayer = Sdf.Layer.FindOrOpen(schemaLayerPath)
    if not schemaLayer:
        Tf.RaiseRuntimeError("Missing schema.usda at path (%s)." \
                %(schemaLayerPath))

    # set skipCodeGeneration  customData to true, unless explicitly marked
    # False in the config file
    skipCodeGeneration = config.get(
            SchemaLayerConstants.SKIP_CODE_GENERATION, True)

    # configure schema.usda
    # fill in sublayers
    _ConfigureSchemaLayer(schemaLayer, schemaSubLayers, skipCodeGeneration)

    # for each sdrNode call updateSchemaFromSdrNode with schema.usda
    for node in sdrNodesToParse:
        assetPathIdentifier = node[1] if type(node) is tuple else ""
        sdrNode = node[0] if type(node) is tuple else node
        UsdUtils.UpdateSchemaWithSdrNode(schemaLayer, sdrNode, renderContext,
                assetPathIdentifier)

    usdGenSchemaCmd = _GetUsdGenSchemaCmd()
    usdGenSchemaArgs = ["--validate"] if validate else []
    if not usdGenSchemaCmd:
        Tf.RaiseRuntimeError("%s not found. Make sure %s is in the PATH." \
                %(USD_GEN_SCHEMA))

    call([usdGenSchemaCmd] + usdGenSchemaArgs, cwd=schemaGenerationPath)

    if writeReadme:
        readMeFile = os.path.join(schemaGenerationPath,
                MiscConstants.README_FILE_NAME)
        description = dedent("""
            The files ("schema.usda", "generatedSchema.usda" and
            "plugInfo.json") in this directory are auto generated using 
            usdgenschemafromsdr utility.

            A schema.usda is populated using sdrNodes which are specified in a
            json config. usdGenSchema is then run on this auto populated schema 
            (with skipCodeGeneration set to True) to output a 
            generatedSchema.usda and plugInfo.json.
            """) if skipCodeGeneration else \
            dedent("""
            The files ("schema.usda", "generatedSchema.usda", "plugInfo.json",
            cpp source and header files) in this directory are auto generated
            using usdgenschemafromsdr utility.

            A schema.usda is populated using sdrNodes which are specified in a
            json config. usdGenSchema is then run on this auto populated schema 
            to output a generatedSchema.usda and plugInfo.json and all the
            generated code.
            """)
        with open(readMeFile, "w") as file:
            file.write(description)
    

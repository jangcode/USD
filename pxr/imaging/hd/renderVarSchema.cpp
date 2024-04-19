//
// Copyright 2023 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
////////////////////////////////////////////////////////////////////////

/* ************************************************************************** */
/* **                                                                      ** */
/* ** This file is generated by a script.                                  ** */
/* **                                                                      ** */
/* ** Do not edit it directly (unless it is within a CUSTOM CODE section)! ** */
/* ** Edit hdSchemaDefs.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#include "pxr/imaging/hd/renderVarSchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdRenderVarSchemaTokens,
    HD_RENDER_VAR_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdPathDataSourceHandle
HdRenderVarSchema::GetPath() const
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdRenderVarSchemaTokens->path);
}

HdTokenDataSourceHandle
HdRenderVarSchema::GetDataType() const
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdRenderVarSchemaTokens->dataType);
}

HdTokenDataSourceHandle
HdRenderVarSchema::GetSourceName() const
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdRenderVarSchemaTokens->sourceName);
}

HdTokenDataSourceHandle
HdRenderVarSchema::GetSourceType() const
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdRenderVarSchemaTokens->sourceType);
}

HdContainerDataSourceHandle
HdRenderVarSchema::GetNamespacedSettings() const
{
    return _GetTypedDataSource<HdContainerDataSource>(
        HdRenderVarSchemaTokens->namespacedSettings);
}

/*static*/
HdContainerDataSourceHandle
HdRenderVarSchema::BuildRetained(
        const HdPathDataSourceHandle &path,
        const HdTokenDataSourceHandle &dataType,
        const HdTokenDataSourceHandle &sourceName,
        const HdTokenDataSourceHandle &sourceType,
        const HdContainerDataSourceHandle &namespacedSettings
)
{
    TfToken _names[5];
    HdDataSourceBaseHandle _values[5];

    size_t _count = 0;

    if (path) {
        _names[_count] = HdRenderVarSchemaTokens->path;
        _values[_count++] = path;
    }

    if (dataType) {
        _names[_count] = HdRenderVarSchemaTokens->dataType;
        _values[_count++] = dataType;
    }

    if (sourceName) {
        _names[_count] = HdRenderVarSchemaTokens->sourceName;
        _values[_count++] = sourceName;
    }

    if (sourceType) {
        _names[_count] = HdRenderVarSchemaTokens->sourceType;
        _values[_count++] = sourceType;
    }

    if (namespacedSettings) {
        _names[_count] = HdRenderVarSchemaTokens->namespacedSettings;
        _values[_count++] = namespacedSettings;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdRenderVarSchema::Builder &
HdRenderVarSchema::Builder::SetPath(
    const HdPathDataSourceHandle &path)
{
    _path = path;
    return *this;
}

HdRenderVarSchema::Builder &
HdRenderVarSchema::Builder::SetDataType(
    const HdTokenDataSourceHandle &dataType)
{
    _dataType = dataType;
    return *this;
}

HdRenderVarSchema::Builder &
HdRenderVarSchema::Builder::SetSourceName(
    const HdTokenDataSourceHandle &sourceName)
{
    _sourceName = sourceName;
    return *this;
}

HdRenderVarSchema::Builder &
HdRenderVarSchema::Builder::SetSourceType(
    const HdTokenDataSourceHandle &sourceType)
{
    _sourceType = sourceType;
    return *this;
}

HdRenderVarSchema::Builder &
HdRenderVarSchema::Builder::SetNamespacedSettings(
    const HdContainerDataSourceHandle &namespacedSettings)
{
    _namespacedSettings = namespacedSettings;
    return *this;
}

HdContainerDataSourceHandle
HdRenderVarSchema::Builder::Build()
{
    return HdRenderVarSchema::BuildRetained(
        _path,
        _dataType,
        _sourceName,
        _sourceType,
        _namespacedSettings
    );
}

/*static*/
HdRenderVarSchema
HdRenderVarSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdRenderVarSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdRenderVarSchemaTokens->renderVar))
        : nullptr);
}

/*static*/
const TfToken &
HdRenderVarSchema::GetSchemaToken()
{
    return HdRenderVarSchemaTokens->renderVar;
}

/*static*/
const HdDataSourceLocator &
HdRenderVarSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(GetSchemaToken());
    return locator;
}

/* static */
const HdDataSourceLocator &
HdRenderVarSchema::GetNamespacedSettingsLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdRenderVarSchemaTokens->namespacedSettings);
    return locator;
} 

PXR_NAMESPACE_CLOSE_SCOPE
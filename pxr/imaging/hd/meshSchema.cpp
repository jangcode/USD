//
// Copyright 2021 Pixar
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
// This file is generated by a script.  Do not edit directly.  Edit the
// schema.template.cpp file to make changes.

#include "pxr/imaging/hd/meshSchema.h"
#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdMeshSchemaTokens,
    HDMESH_SCHEMA_TOKENS);



HdMeshTopologySchema
HdMeshSchema::GetTopology()
{
    return HdMeshTopologySchema(_GetTypedDataSource<HdContainerDataSource>(
        HdMeshSchemaTokens->topology));
}

HdTokenDataSourceHandle
HdMeshSchema::GetSubdivisionScheme()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdMeshSchemaTokens->subdivisionScheme);
}

HdSubdivisionTagsSchema
HdMeshSchema::GetSubdivisionTags()
{
    return HdSubdivisionTagsSchema(_GetTypedDataSource<HdContainerDataSource>(
        HdMeshSchemaTokens->subdivisionTags));
}

HdGeomSubsetsSchema
HdMeshSchema::GetGeomSubsets()
{
    return HdGeomSubsetsSchema(_GetTypedDataSource<HdContainerDataSource>(
        HdMeshSchemaTokens->geomSubsets));
}

HdBoolDataSourceHandle
HdMeshSchema::GetDoubleSided()
{
    return _GetTypedDataSource<HdBoolDataSource>(
        HdMeshSchemaTokens->doubleSided);
}

/*static*/
HdContainerDataSourceHandle
HdMeshSchema::BuildRetained(
        const HdContainerDataSourceHandle &topology,
        const HdTokenDataSourceHandle &subdivisionScheme,
        const HdContainerDataSourceHandle &subdivisionTags,
        const HdContainerDataSourceHandle &geomSubsets,
        const HdBoolDataSourceHandle &doubleSided
)
{
    TfToken names[5];
    HdDataSourceBaseHandle values[5];

    size_t count = 0;
    if (topology) {
        names[count] = HdMeshSchemaTokens->topology;
        values[count++] = topology;
    }

    if (subdivisionScheme) {
        names[count] = HdMeshSchemaTokens->subdivisionScheme;
        values[count++] = subdivisionScheme;
    }

    if (subdivisionTags) {
        names[count] = HdMeshSchemaTokens->subdivisionTags;
        values[count++] = subdivisionTags;
    }

    if (geomSubsets) {
        names[count] = HdMeshSchemaTokens->geomSubsets;
        values[count++] = geomSubsets;
    }

    if (doubleSided) {
        names[count] = HdMeshSchemaTokens->doubleSided;
        values[count++] = doubleSided;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdMeshSchema
HdMeshSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdMeshSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdMeshSchemaTokens->mesh))
        : nullptr);
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh
    );
    return locator;
} 
/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetTopologyLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh,
        HdMeshSchemaTokens->topology
    );
    return locator;
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetGeomSubsetsLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh,
        HdMeshSchemaTokens->geomSubsets
    );
    return locator;
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetDoubleSidedLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh,
        HdMeshSchemaTokens->doubleSided
    );
    return locator;
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetSubdivisionTagsLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh,
        HdMeshSchemaTokens->subdivisionTags
    );
    return locator;
}

/*static*/
const HdDataSourceLocator &
HdMeshSchema::GetSubdivisionSchemeLocator()
{
    static const HdDataSourceLocator locator(
        HdMeshSchemaTokens->mesh,
        HdMeshSchemaTokens->subdivisionScheme
    );
    return locator;
}


HdMeshSchema::Builder &
HdMeshSchema::Builder::SetTopology(
    const HdContainerDataSourceHandle &topology)
{
    _topology = topology;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetSubdivisionScheme(
    const HdTokenDataSourceHandle &subdivisionScheme)
{
    _subdivisionScheme = subdivisionScheme;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetSubdivisionTags(
    const HdContainerDataSourceHandle &subdivisionTags)
{
    _subdivisionTags = subdivisionTags;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetGeomSubsets(
    const HdContainerDataSourceHandle &geomSubsets)
{
    _geomSubsets = geomSubsets;
    return *this;
}

HdMeshSchema::Builder &
HdMeshSchema::Builder::SetDoubleSided(
    const HdBoolDataSourceHandle &doubleSided)
{
    _doubleSided = doubleSided;
    return *this;
}

HdContainerDataSourceHandle
HdMeshSchema::Builder::Build()
{
    return HdMeshSchema::BuildRetained(
        _topology,
        _subdivisionScheme,
        _subdivisionTags,
        _geomSubsets,
        _doubleSided
    );
}


PXR_NAMESPACE_CLOSE_SCOPE
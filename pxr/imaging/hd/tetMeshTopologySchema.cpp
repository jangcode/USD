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
/* ** Edit hdGen/schema.py instead to make changes.                        ** */
/* **                                                                      ** */
/* ************************************************************************** */

#include "pxr/imaging/hd/tetMeshTopologySchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"
#include "pxr/imaging/hd/tetMeshSchema.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdTetMeshTopologySchemaTokens,
    HD_TET_MESH_TOPOLOGY_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdVec4iArrayDataSourceHandle
HdTetMeshTopologySchema::GetTetVertexIndices()
{
    return _GetTypedDataSource<HdVec4iArrayDataSource>(
        HdTetMeshTopologySchemaTokens->tetVertexIndices);
}

HdTokenDataSourceHandle
HdTetMeshTopologySchema::GetOrientation()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdTetMeshTopologySchemaTokens->orientation);
}

/*static*/
HdContainerDataSourceHandle
HdTetMeshTopologySchema::BuildRetained(
        const HdVec4iArrayDataSourceHandle &tetVertexIndices,
        const HdTokenDataSourceHandle &orientation
)
{
    TfToken _names[2];
    HdDataSourceBaseHandle _values[2];

    size_t _count = 0;

    if (tetVertexIndices) {
        _names[_count] = HdTetMeshTopologySchemaTokens->tetVertexIndices;
        _values[_count++] = tetVertexIndices;
    }

    if (orientation) {
        _names[_count] = HdTetMeshTopologySchemaTokens->orientation;
        _values[_count++] = orientation;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdTetMeshTopologySchema::Builder &
HdTetMeshTopologySchema::Builder::SetTetVertexIndices(
    const HdVec4iArrayDataSourceHandle &tetVertexIndices)
{
    _tetVertexIndices = tetVertexIndices;
    return *this;
}

HdTetMeshTopologySchema::Builder &
HdTetMeshTopologySchema::Builder::SetOrientation(
    const HdTokenDataSourceHandle &orientation)
{
    _orientation = orientation;
    return *this;
}

HdContainerDataSourceHandle
HdTetMeshTopologySchema::Builder::Build()
{
    return HdTetMeshTopologySchema::BuildRetained(
        _tetVertexIndices,
        _orientation
    );
}

/*static*/
HdTetMeshTopologySchema
HdTetMeshTopologySchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdTetMeshTopologySchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdTetMeshTopologySchemaTokens->topology))
        : nullptr);
}

/*static*/
const TfToken &
HdTetMeshTopologySchema::GetSchemaToken()
{
    return HdTetMeshTopologySchemaTokens->topology;
}

/*static*/
const HdDataSourceLocator &
HdTetMeshTopologySchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator =
        HdTetMeshSchema::GetDefaultLocator().Append(GetSchemaToken());
    return locator;
}

/* static */
const HdDataSourceLocator &
HdTetMeshTopologySchema::GetTetVertexIndicesLocator()
{
    static const HdDataSourceLocator locator =
        GetDefaultLocator().Append(
            HdTetMeshTopologySchemaTokens->tetVertexIndices);
    return locator;
}

/*static*/
HdTokenDataSourceHandle
HdTetMeshTopologySchema::BuildOrientationDataSource(
    const TfToken &orientation)
{

    if (orientation == HdTetMeshTopologySchemaTokens->leftHanded) {
        static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
            HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
        return ds;
    }
    if (orientation == HdTetMeshTopologySchemaTokens->rightHanded) {
        static const HdRetainedTypedSampledDataSource<TfToken>::Handle ds =
            HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
        return ds;
    }
    // fallback for unknown token
    return HdRetainedTypedSampledDataSource<TfToken>::New(orientation);
} 

PXR_NAMESPACE_CLOSE_SCOPE
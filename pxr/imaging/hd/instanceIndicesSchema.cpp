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

#include "pxr/imaging/hd/instanceIndicesSchema.h"

#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"

// --(BEGIN CUSTOM CODE: Includes)--
// --(END CUSTOM CODE: Includes)--

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdInstanceIndicesSchemaTokens,
    HD_INSTANCE_INDICES_SCHEMA_TOKENS);

// --(BEGIN CUSTOM CODE: Schema Methods)--
// --(END CUSTOM CODE: Schema Methods)--

HdPathDataSourceHandle
HdInstanceIndicesSchema::GetInstancer() const
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdInstanceIndicesSchemaTokens->instancer);
}

HdIntDataSourceHandle
HdInstanceIndicesSchema::GetPrototypeIndex() const
{
    return _GetTypedDataSource<HdIntDataSource>(
        HdInstanceIndicesSchemaTokens->prototypeIndex);
}

HdIntArrayDataSourceHandle
HdInstanceIndicesSchema::GetInstanceIndices() const
{
    return _GetTypedDataSource<HdIntArrayDataSource>(
        HdInstanceIndicesSchemaTokens->instanceIndices);
}

/*static*/
HdContainerDataSourceHandle
HdInstanceIndicesSchema::BuildRetained(
        const HdPathDataSourceHandle &instancer,
        const HdIntDataSourceHandle &prototypeIndex,
        const HdIntArrayDataSourceHandle &instanceIndices
)
{
    TfToken _names[3];
    HdDataSourceBaseHandle _values[3];

    size_t _count = 0;

    if (instancer) {
        _names[_count] = HdInstanceIndicesSchemaTokens->instancer;
        _values[_count++] = instancer;
    }

    if (prototypeIndex) {
        _names[_count] = HdInstanceIndicesSchemaTokens->prototypeIndex;
        _values[_count++] = prototypeIndex;
    }

    if (instanceIndices) {
        _names[_count] = HdInstanceIndicesSchemaTokens->instanceIndices;
        _values[_count++] = instanceIndices;
    }
    return HdRetainedContainerDataSource::New(_count, _names, _values);
}

HdInstanceIndicesSchema::Builder &
HdInstanceIndicesSchema::Builder::SetInstancer(
    const HdPathDataSourceHandle &instancer)
{
    _instancer = instancer;
    return *this;
}

HdInstanceIndicesSchema::Builder &
HdInstanceIndicesSchema::Builder::SetPrototypeIndex(
    const HdIntDataSourceHandle &prototypeIndex)
{
    _prototypeIndex = prototypeIndex;
    return *this;
}

HdInstanceIndicesSchema::Builder &
HdInstanceIndicesSchema::Builder::SetInstanceIndices(
    const HdIntArrayDataSourceHandle &instanceIndices)
{
    _instanceIndices = instanceIndices;
    return *this;
}

HdContainerDataSourceHandle
HdInstanceIndicesSchema::Builder::Build()
{
    return HdInstanceIndicesSchema::BuildRetained(
        _instancer,
        _prototypeIndex,
        _instanceIndices
    );
} 

PXR_NAMESPACE_CLOSE_SCOPE
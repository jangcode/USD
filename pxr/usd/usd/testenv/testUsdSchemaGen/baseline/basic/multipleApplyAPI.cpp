//
// Copyright 2016 Pixar
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
#include "pxr/usd/usdContrived/multipleApplyAPI.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

#include "pxr/base/tf/staticTokens.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdContrivedMultipleApplyAPI,
        TfType::Bases< UsdAPISchemaBase > >();
    
}

TF_DEFINE_PRIVATE_TOKENS(
    _schemaTokens,
    (test)
);

/* virtual */
UsdContrivedMultipleApplyAPI::~UsdContrivedMultipleApplyAPI()
{
}

/* static */
UsdContrivedMultipleApplyAPI
UsdContrivedMultipleApplyAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdContrivedMultipleApplyAPI();
    }
    TfToken name;
    if (!IsMultipleApplyAPIPath(path, &name)) {
        TF_CODING_ERROR("Invalid test path <%s>.", path.GetText());
        return UsdContrivedMultipleApplyAPI();
    }
    return UsdContrivedMultipleApplyAPI(stage->GetPrimAtPath(path.GetPrimPath()), name);
}

UsdContrivedMultipleApplyAPI
UsdContrivedMultipleApplyAPI::Get(const UsdPrim &prim, const TfToken &name)
{
    return UsdContrivedMultipleApplyAPI(prim, name);
}

/* static */
std::vector<UsdContrivedMultipleApplyAPI>
UsdContrivedMultipleApplyAPI::GetAll(const UsdPrim &prim)
{
    std::vector<UsdContrivedMultipleApplyAPI> schemas;
    
    for (const auto &schemaName :
         UsdAPISchemaBase::_GetMultipleApplyInstanceNames(prim, _GetStaticTfType())) {
        schemas.emplace_back(prim, schemaName);
    }

    return schemas;
}


/* static */
bool 
UsdContrivedMultipleApplyAPI::IsSchemaPropertyBaseName(const TfToken &baseName)
{
    static TfTokenVector attrsAndRels = {
        UsdSchemaRegistry::GetMultipleApplyNameTemplateBaseName(
            UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrOne),
        UsdSchemaRegistry::GetMultipleApplyNameTemplateBaseName(
            UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrTwo),
    };

    return find(attrsAndRels.begin(), attrsAndRels.end(), baseName)
            != attrsAndRels.end();
}

/* static */
bool
UsdContrivedMultipleApplyAPI::IsMultipleApplyAPIPath(
    const SdfPath &path, TfToken *name)
{
    if (!path.IsPropertyPath()) {
        return false;
    }

    std::string propertyName = path.GetName();
    TfTokenVector tokens = SdfPath::TokenizeIdentifierAsTokens(propertyName);

    // The baseName of the  path can't be one of the 
    // schema properties. We should validate this in the creation (or apply)
    // API.
    TfToken baseName = *tokens.rbegin();
    if (IsSchemaPropertyBaseName(baseName)) {
        return false;
    }

    if (tokens.size() >= 2
        && tokens[0] == _schemaTokens->test) {
        *name = TfToken(propertyName.substr(
            _schemaTokens->test.GetString().size() + 1));
        return true;
    }

    return false;
}

/* virtual */
UsdSchemaKind UsdContrivedMultipleApplyAPI::_GetSchemaKind() const
{
    return UsdContrivedMultipleApplyAPI::schemaKind;
}

/* static */
bool
UsdContrivedMultipleApplyAPI::CanApply(
    const UsdPrim &prim, const TfToken &name, std::string *whyNot)
{
    return prim.CanApplyAPI<UsdContrivedMultipleApplyAPI>(name, whyNot);
}

/* static */
UsdContrivedMultipleApplyAPI
UsdContrivedMultipleApplyAPI::Apply(const UsdPrim &prim, const TfToken &name)
{
    if (prim.ApplyAPI<UsdContrivedMultipleApplyAPI>(name)) {
        return UsdContrivedMultipleApplyAPI(prim, name);
    }
    return UsdContrivedMultipleApplyAPI();
}

/* static */
const TfType &
UsdContrivedMultipleApplyAPI::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdContrivedMultipleApplyAPI>();
    return tfType;
}

/* static */
bool 
UsdContrivedMultipleApplyAPI::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdContrivedMultipleApplyAPI::_GetTfType() const
{
    return _GetStaticTfType();
}

/// Returns the property name prefixed with the correct namespace prefix, which
/// is composed of the the API's propertyNamespacePrefix metadata and the
/// instance name of the API.
static inline
TfToken
_GetNamespacedPropertyName(const TfToken instanceName, const TfToken propName)
{
    return UsdSchemaRegistry::MakeMultipleApplyNameInstance(propName, instanceName);
}

UsdAttribute
UsdContrivedMultipleApplyAPI::GetTestAttrOneAttr() const
{
    return GetPrim().GetAttribute(
        _GetNamespacedPropertyName(
            GetName(),
            UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrOne));
}

UsdAttribute
UsdContrivedMultipleApplyAPI::CreateTestAttrOneAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(
                       _GetNamespacedPropertyName(
                            GetName(),
                           UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrOne),
                       SdfValueTypeNames->Int,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdContrivedMultipleApplyAPI::GetTestAttrTwoAttr() const
{
    return GetPrim().GetAttribute(
        _GetNamespacedPropertyName(
            GetName(),
            UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrTwo));
}

UsdAttribute
UsdContrivedMultipleApplyAPI::CreateTestAttrTwoAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(
                       _GetNamespacedPropertyName(
                            GetName(),
                           UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrTwo),
                       SdfValueTypeNames->Double,
                       /* custom = */ false,
                       SdfVariabilityVarying,
                       defaultValue,
                       writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
UsdContrivedMultipleApplyAPI::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrOne,
        UsdContrivedTokens->test_MultipleApplyTemplate_TestAttrTwo,
    };
    static TfTokenVector allNames =
        _ConcatenateAttributeNames(
            UsdAPISchemaBase::GetSchemaAttributeNames(true),
            localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

/*static*/
TfTokenVector
UsdContrivedMultipleApplyAPI::GetSchemaAttributeNames(
    bool includeInherited, const TfToken &instanceName)
{
    const TfTokenVector &attrNames = GetSchemaAttributeNames(includeInherited);
    if (instanceName.IsEmpty()) {
        return attrNames;
    }
    TfTokenVector result;
    result.reserve(attrNames.size());
    for (const TfToken &attrName : attrNames) {
        result.push_back(
            UsdSchemaRegistry::MakeMultipleApplyNameInstance(attrName, instanceName));
    }
    return result;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SoftDesignTrainingMainCharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingMainCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UCameraComponent_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UMaterialInterface_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USpringArmComponent_NoRegister();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASoftDesignTrainingMainCharacter *****************************************
void ASoftDesignTrainingMainCharacter::StaticRegisterNativesASoftDesignTrainingMainCharacter()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter;
UClass* ASoftDesignTrainingMainCharacter::GetPrivateStaticClass()
{
	using TClass = ASoftDesignTrainingMainCharacter;
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoftDesignTrainingMainCharacter"),
			Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.InnerSingleton,
			StaticRegisterNativesASoftDesignTrainingMainCharacter,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter_NoRegister()
{
	return ASoftDesignTrainingMainCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SoftDesignTrainingMainCharacter.h" },
		{ "ModuleRelativePath", "SoftDesignTrainingMainCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_m_TopDownCameraComponent_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SoftDesignTrainingMainCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_m_CameraBoom_MetaData[] = {
		{ "AllowPrivateAccess", "true" },
		{ "Category", "Camera" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "SoftDesignTrainingMainCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_m_PowerUpDuration_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "SoftDesignTrainingMainCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_m_PoweredUpMaterial_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "SoftDesignTrainingMainCharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_m_TopDownCameraComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_m_CameraBoom;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_m_PowerUpDuration;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_m_PoweredUpMaterial;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASoftDesignTrainingMainCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_TopDownCameraComponent = { "m_TopDownCameraComponent", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_TopDownCameraComponent), Z_Construct_UClass_UCameraComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_m_TopDownCameraComponent_MetaData), NewProp_m_TopDownCameraComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_CameraBoom = { "m_CameraBoom", nullptr, (EPropertyFlags)0x00200800000a001d, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_CameraBoom), Z_Construct_UClass_USpringArmComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_m_CameraBoom_MetaData), NewProp_m_CameraBoom_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_PowerUpDuration = { "m_PowerUpDuration", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_PowerUpDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_m_PowerUpDuration_MetaData), NewProp_m_PowerUpDuration_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_PoweredUpMaterial = { "m_PoweredUpMaterial", nullptr, (EPropertyFlags)0x0020080000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASoftDesignTrainingMainCharacter, m_PoweredUpMaterial), Z_Construct_UClass_UMaterialInterface_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_m_PoweredUpMaterial_MetaData), NewProp_m_PoweredUpMaterial_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_TopDownCameraComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_CameraBoom,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_PowerUpDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::NewProp_m_PoweredUpMaterial,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ASoftDesignTrainingCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::ClassParams = {
	&ASoftDesignTrainingMainCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASoftDesignTrainingMainCharacter()
{
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.OuterSingleton, Z_Construct_UClass_ASoftDesignTrainingMainCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingMainCharacter);
ASoftDesignTrainingMainCharacter::~ASoftDesignTrainingMainCharacter() {}
// ********** End Class ASoftDesignTrainingMainCharacter *******************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASoftDesignTrainingMainCharacter, ASoftDesignTrainingMainCharacter::StaticClass, TEXT("ASoftDesignTrainingMainCharacter"), &Z_Registration_Info_UClass_ASoftDesignTrainingMainCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASoftDesignTrainingMainCharacter), 1827225861U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h__Script_SoftDesignTraining_3043223341(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingMainCharacter_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

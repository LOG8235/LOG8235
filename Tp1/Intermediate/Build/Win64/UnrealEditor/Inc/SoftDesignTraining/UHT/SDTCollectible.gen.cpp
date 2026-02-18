// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SDTCollectible.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSDTCollectible() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AStaticMeshActor();
ENGINE_API UClass* Z_Construct_UClass_UParticleSystem_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTCollectible();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTCollectible_NoRegister();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASDTCollectible **********************************************************
void ASDTCollectible::StaticRegisterNativesASDTCollectible()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASDTCollectible;
UClass* ASDTCollectible::GetPrivateStaticClass()
{
	using TClass = ASDTCollectible;
	if (!Z_Registration_Info_UClass_ASDTCollectible.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SDTCollectible"),
			Z_Registration_Info_UClass_ASDTCollectible.InnerSingleton,
			StaticRegisterNativesASDTCollectible,
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
	return Z_Registration_Info_UClass_ASDTCollectible.InnerSingleton;
}
UClass* Z_Construct_UClass_ASDTCollectible_NoRegister()
{
	return ASDTCollectible::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASDTCollectible_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Input" },
		{ "IncludePath", "SDTCollectible.h" },
		{ "ModuleRelativePath", "SDTCollectible.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_m_CollectCooldownDuration_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "SDTCollectible.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_isMoveable_MetaData[] = {
		{ "Category", "AI" },
		{ "ModuleRelativePath", "SDTCollectible.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollectSound_MetaData[] = {
		{ "Category", "Effects" },
		{ "ModuleRelativePath", "SDTCollectible.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollectEffect_MetaData[] = {
		{ "Category", "Effects" },
		{ "ModuleRelativePath", "SDTCollectible.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_m_CollectCooldownDuration;
	static void NewProp_isMoveable_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_isMoveable;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollectSound;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_CollectEffect;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASDTCollectible>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTCollectible_Statics::NewProp_m_CollectCooldownDuration = { "m_CollectCooldownDuration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTCollectible, m_CollectCooldownDuration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_m_CollectCooldownDuration_MetaData), NewProp_m_CollectCooldownDuration_MetaData) };
void Z_Construct_UClass_ASDTCollectible_Statics::NewProp_isMoveable_SetBit(void* Obj)
{
	((ASDTCollectible*)Obj)->isMoveable = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASDTCollectible_Statics::NewProp_isMoveable = { "isMoveable", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASDTCollectible), &Z_Construct_UClass_ASDTCollectible_Statics::NewProp_isMoveable_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_isMoveable_MetaData), NewProp_isMoveable_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASDTCollectible_Statics::NewProp_CollectSound = { "CollectSound", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTCollectible, CollectSound), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollectSound_MetaData), NewProp_CollectSound_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASDTCollectible_Statics::NewProp_CollectEffect = { "CollectEffect", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTCollectible, CollectEffect), Z_Construct_UClass_UParticleSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollectEffect_MetaData), NewProp_CollectEffect_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASDTCollectible_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTCollectible_Statics::NewProp_m_CollectCooldownDuration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTCollectible_Statics::NewProp_isMoveable,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTCollectible_Statics::NewProp_CollectSound,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTCollectible_Statics::NewProp_CollectEffect,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTCollectible_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASDTCollectible_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AStaticMeshActor,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTCollectible_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASDTCollectible_Statics::ClassParams = {
	&ASDTCollectible::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASDTCollectible_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASDTCollectible_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTCollectible_Statics::Class_MetaDataParams), Z_Construct_UClass_ASDTCollectible_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASDTCollectible()
{
	if (!Z_Registration_Info_UClass_ASDTCollectible.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASDTCollectible.OuterSingleton, Z_Construct_UClass_ASDTCollectible_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASDTCollectible.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASDTCollectible);
ASDTCollectible::~ASDTCollectible() {}
// ********** End Class ASDTCollectible ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTCollectible_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASDTCollectible, ASDTCollectible::StaticClass, TEXT("ASDTCollectible"), &Z_Registration_Info_UClass_ASDTCollectible, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASDTCollectible), 3582017263U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTCollectible_h__Script_SoftDesignTraining_3836309220(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTCollectible_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTCollectible_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

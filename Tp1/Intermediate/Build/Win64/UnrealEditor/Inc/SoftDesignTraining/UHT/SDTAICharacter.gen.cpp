// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SDTAICharacter.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSDTAICharacter() {}

// ********** Begin Cross Module References ********************************************************
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTAICharacter();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTAICharacter_NoRegister();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASDTAICharacter **********************************************************
void ASDTAICharacter::StaticRegisterNativesASDTAICharacter()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASDTAICharacter;
UClass* ASDTAICharacter::GetPrivateStaticClass()
{
	using TClass = ASDTAICharacter;
	if (!Z_Registration_Info_UClass_ASDTAICharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SDTAICharacter"),
			Z_Registration_Info_UClass_ASDTAICharacter.InnerSingleton,
			StaticRegisterNativesASDTAICharacter,
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
	return Z_Registration_Info_UClass_ASDTAICharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ASDTAICharacter_NoRegister()
{
	return ASDTAICharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASDTAICharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SDTAICharacter.h" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxSpeed_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Acceleration_MetaData[] = {
		{ "Category", "Movement" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WallDetectionDistance_MetaData[] = {
		{ "Category", "AI|Wall Avoidance" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AvoidTurnRateDegPerSec_MetaData[] = {
		{ "Category", "AI|Wall Avoidance" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawWallDebug_MetaData[] = {
		{ "Category", "AI|Wall Avoidance" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_playerDetectionRadius_MetaData[] = {
		{ "Category", "AI|Player Chase" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_collectibleDetectionRadius_MetaData[] = {
		{ "Category", "AI|Collectible Chase" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawPursuitDebug_MetaData[] = {
		{ "Category", "AI|Player Chase" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDrawCollectibleDebug_MetaData[] = {
		{ "Category", "AI|Collectible Chase" },
		{ "ModuleRelativePath", "SDTAICharacter.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxSpeed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Acceleration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WallDetectionDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AvoidTurnRateDegPerSec;
	static void NewProp_bDrawWallDebug_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawWallDebug;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_playerDetectionRadius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_collectibleDetectionRadius;
	static void NewProp_bDrawPursuitDebug_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawPursuitDebug;
	static void NewProp_bDrawCollectibleDebug_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDrawCollectibleDebug;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASDTAICharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_MaxSpeed = { "MaxSpeed", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, MaxSpeed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxSpeed_MetaData), NewProp_MaxSpeed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_Acceleration = { "Acceleration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, Acceleration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Acceleration_MetaData), NewProp_Acceleration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_WallDetectionDistance = { "WallDetectionDistance", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, WallDetectionDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WallDetectionDistance_MetaData), NewProp_WallDetectionDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_AvoidTurnRateDegPerSec = { "AvoidTurnRateDegPerSec", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, AvoidTurnRateDegPerSec), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AvoidTurnRateDegPerSec_MetaData), NewProp_AvoidTurnRateDegPerSec_MetaData) };
void Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawWallDebug_SetBit(void* Obj)
{
	((ASDTAICharacter*)Obj)->bDrawWallDebug = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawWallDebug = { "bDrawWallDebug", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASDTAICharacter), &Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawWallDebug_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawWallDebug_MetaData), NewProp_bDrawWallDebug_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_playerDetectionRadius = { "playerDetectionRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, playerDetectionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_playerDetectionRadius_MetaData), NewProp_playerDetectionRadius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_collectibleDetectionRadius = { "collectibleDetectionRadius", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ASDTAICharacter, collectibleDetectionRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_collectibleDetectionRadius_MetaData), NewProp_collectibleDetectionRadius_MetaData) };
void Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawPursuitDebug_SetBit(void* Obj)
{
	((ASDTAICharacter*)Obj)->bDrawPursuitDebug = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawPursuitDebug = { "bDrawPursuitDebug", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASDTAICharacter), &Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawPursuitDebug_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawPursuitDebug_MetaData), NewProp_bDrawPursuitDebug_MetaData) };
void Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawCollectibleDebug_SetBit(void* Obj)
{
	((ASDTAICharacter*)Obj)->bDrawCollectibleDebug = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawCollectibleDebug = { "bDrawCollectibleDebug", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ASDTAICharacter), &Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawCollectibleDebug_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDrawCollectibleDebug_MetaData), NewProp_bDrawCollectibleDebug_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASDTAICharacter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_MaxSpeed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_Acceleration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_WallDetectionDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_AvoidTurnRateDegPerSec,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawWallDebug,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_playerDetectionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_collectibleDetectionRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawPursuitDebug,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASDTAICharacter_Statics::NewProp_bDrawCollectibleDebug,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTAICharacter_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ASDTAICharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ASoftDesignTrainingCharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTAICharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASDTAICharacter_Statics::ClassParams = {
	&ASDTAICharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_ASDTAICharacter_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_ASDTAICharacter_Statics::PropPointers),
	0,
	0x009001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASDTAICharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASDTAICharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASDTAICharacter()
{
	if (!Z_Registration_Info_UClass_ASDTAICharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASDTAICharacter.OuterSingleton, Z_Construct_UClass_ASDTAICharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASDTAICharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASDTAICharacter);
ASDTAICharacter::~ASDTAICharacter() {}
// ********** End Class ASDTAICharacter ************************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAICharacter_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASDTAICharacter, ASDTAICharacter::StaticClass, TEXT("ASDTAICharacter"), &Z_Registration_Info_UClass_ASDTAICharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASDTAICharacter), 1428094646U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAICharacter_h__Script_SoftDesignTraining_623110581(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAICharacter_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAICharacter_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

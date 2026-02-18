// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SoftDesignTrainingGameMode.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingGameMode() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AGameMode();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASoftDesignTrainingGameMode **********************************************
void ASoftDesignTrainingGameMode::StaticRegisterNativesASoftDesignTrainingGameMode()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASoftDesignTrainingGameMode;
UClass* ASoftDesignTrainingGameMode::GetPrivateStaticClass()
{
	using TClass = ASoftDesignTrainingGameMode;
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoftDesignTrainingGameMode"),
			Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.InnerSingleton,
			StaticRegisterNativesASoftDesignTrainingGameMode,
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
	return Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.InnerSingleton;
}
UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode_NoRegister()
{
	return ASoftDesignTrainingGameMode::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "SoftDesignTrainingGameMode.h" },
		{ "ModuleRelativePath", "SoftDesignTrainingGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASoftDesignTrainingGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameMode,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::ClassParams = {
	&ASoftDesignTrainingGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008803ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASoftDesignTrainingGameMode()
{
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.OuterSingleton, Z_Construct_UClass_ASoftDesignTrainingGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASoftDesignTrainingGameMode.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingGameMode);
ASoftDesignTrainingGameMode::~ASoftDesignTrainingGameMode() {}
// ********** End Class ASoftDesignTrainingGameMode ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingGameMode_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASoftDesignTrainingGameMode, ASoftDesignTrainingGameMode::StaticClass, TEXT("ASoftDesignTrainingGameMode"), &Z_Registration_Info_UClass_ASoftDesignTrainingGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASoftDesignTrainingGameMode), 2907177304U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingGameMode_h__Script_SoftDesignTraining_1700794864(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingGameMode_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingGameMode_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

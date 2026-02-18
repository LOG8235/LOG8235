// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SoftDesignTrainingPlayerController.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingPlayerController() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_APlayerController();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController_NoRegister();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASoftDesignTrainingPlayerController **************************************
void ASoftDesignTrainingPlayerController::StaticRegisterNativesASoftDesignTrainingPlayerController()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController;
UClass* ASoftDesignTrainingPlayerController::GetPrivateStaticClass()
{
	using TClass = ASoftDesignTrainingPlayerController;
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoftDesignTrainingPlayerController"),
			Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.InnerSingleton,
			StaticRegisterNativesASoftDesignTrainingPlayerController,
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
	return Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.InnerSingleton;
}
UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController_NoRegister()
{
	return ASoftDesignTrainingPlayerController::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Collision Rendering Transformation" },
		{ "IncludePath", "SoftDesignTrainingPlayerController.h" },
		{ "ModuleRelativePath", "SoftDesignTrainingPlayerController.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASoftDesignTrainingPlayerController>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_APlayerController,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::ClassParams = {
	&ASoftDesignTrainingPlayerController::StaticClass,
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
	0x008003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::Class_MetaDataParams), Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASoftDesignTrainingPlayerController()
{
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.OuterSingleton, Z_Construct_UClass_ASoftDesignTrainingPlayerController_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingPlayerController);
ASoftDesignTrainingPlayerController::~ASoftDesignTrainingPlayerController() {}
// ********** End Class ASoftDesignTrainingPlayerController ****************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingPlayerController_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASoftDesignTrainingPlayerController, ASoftDesignTrainingPlayerController::StaticClass, TEXT("ASoftDesignTrainingPlayerController"), &Z_Registration_Info_UClass_ASoftDesignTrainingPlayerController, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASoftDesignTrainingPlayerController), 408429364U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingPlayerController_h__Script_SoftDesignTraining_119094321(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingPlayerController_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingPlayerController_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

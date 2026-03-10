// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SoftDesignTraining/SoftDesignTrainingCharacter.h"
#include "Engine/HitResult.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSoftDesignTrainingCharacter() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_ACharacter();
ENGINE_API UClass* Z_Construct_UClass_UPrimitiveComponent_NoRegister();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FHitResult();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter();
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter_NoRegister();
UPackage* Z_Construct_UPackage__Script_SoftDesignTraining();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ASoftDesignTrainingCharacter Function OnBeginOverlap *********************
struct Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics
{
	struct SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms
	{
		UPrimitiveComponent* OverlappedComponent;
		AActor* OtherActor;
		UPrimitiveComponent* OtherComponent;
		int32 OtherBodyIndex;
		bool bFromSweep;
		FHitResult SweepResult;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "SoftDesignTrainingCharacter.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OverlappedComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OtherComponent_MetaData[] = {
		{ "EditInline", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SweepResult_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OverlappedComponent;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherActor;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_OtherComponent;
	static const UECodeGen_Private::FIntPropertyParams NewProp_OtherBodyIndex;
	static void NewProp_bFromSweep_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFromSweep;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SweepResult;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OverlappedComponent = { "OverlappedComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms, OverlappedComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OverlappedComponent_MetaData), NewProp_OverlappedComponent_MetaData) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherActor = { "OtherActor", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms, OtherActor), Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherComponent = { "OtherComponent", nullptr, (EPropertyFlags)0x0010000000080080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms, OtherComponent), Z_Construct_UClass_UPrimitiveComponent_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OtherComponent_MetaData), NewProp_OtherComponent_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherBodyIndex = { "OtherBodyIndex", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms, OtherBodyIndex), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_bFromSweep_SetBit(void* Obj)
{
	((SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms*)Obj)->bFromSweep = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_bFromSweep = { "bFromSweep", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms), &Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_bFromSweep_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_SweepResult = { "SweepResult", nullptr, (EPropertyFlags)0x0010008008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms, SweepResult), Z_Construct_UScriptStruct_FHitResult, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SweepResult_MetaData), NewProp_SweepResult_MetaData) }; // 267591329
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OverlappedComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherActor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherComponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_OtherBodyIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_bFromSweep,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::NewProp_SweepResult,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ASoftDesignTrainingCharacter, nullptr, "OnBeginOverlap", Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::PropPointers), sizeof(Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00480400, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::Function_MetaDataParams), Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::SoftDesignTrainingCharacter_eventOnBeginOverlap_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ASoftDesignTrainingCharacter::execOnBeginOverlap)
{
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OverlappedComponent);
	P_GET_OBJECT(AActor,Z_Param_OtherActor);
	P_GET_OBJECT(UPrimitiveComponent,Z_Param_OtherComponent);
	P_GET_PROPERTY(FIntProperty,Z_Param_OtherBodyIndex);
	P_GET_UBOOL(Z_Param_bFromSweep);
	P_GET_STRUCT_REF(FHitResult,Z_Param_Out_SweepResult);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->OnBeginOverlap(Z_Param_OverlappedComponent,Z_Param_OtherActor,Z_Param_OtherComponent,Z_Param_OtherBodyIndex,Z_Param_bFromSweep,Z_Param_Out_SweepResult);
	P_NATIVE_END;
}
// ********** End Class ASoftDesignTrainingCharacter Function OnBeginOverlap ***********************

// ********** Begin Class ASoftDesignTrainingCharacter *********************************************
void ASoftDesignTrainingCharacter::StaticRegisterNativesASoftDesignTrainingCharacter()
{
	UClass* Class = ASoftDesignTrainingCharacter::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "OnBeginOverlap", &ASoftDesignTrainingCharacter::execOnBeginOverlap },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ASoftDesignTrainingCharacter;
UClass* ASoftDesignTrainingCharacter::GetPrivateStaticClass()
{
	using TClass = ASoftDesignTrainingCharacter;
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SoftDesignTrainingCharacter"),
			Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.InnerSingleton,
			StaticRegisterNativesASoftDesignTrainingCharacter,
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
	return Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.InnerSingleton;
}
UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter_NoRegister()
{
	return ASoftDesignTrainingCharacter::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Navigation" },
		{ "IncludePath", "SoftDesignTrainingCharacter.h" },
		{ "ModuleRelativePath", "SoftDesignTrainingCharacter.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ASoftDesignTrainingCharacter_OnBeginOverlap, "OnBeginOverlap" }, // 2771889646
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASoftDesignTrainingCharacter>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_ACharacter,
	(UObject* (*)())Z_Construct_UPackage__Script_SoftDesignTraining,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::ClassParams = {
	&ASoftDesignTrainingCharacter::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x008001A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::Class_MetaDataParams), Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter()
{
	if (!Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.OuterSingleton, Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ASoftDesignTrainingCharacter.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ASoftDesignTrainingCharacter);
ASoftDesignTrainingCharacter::~ASoftDesignTrainingCharacter() {}
// ********** End Class ASoftDesignTrainingCharacter ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h__Script_SoftDesignTraining_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ASoftDesignTrainingCharacter, ASoftDesignTrainingCharacter::StaticClass, TEXT("ASoftDesignTrainingCharacter"), &Z_Registration_Info_UClass_ASoftDesignTrainingCharacter, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ASoftDesignTrainingCharacter), 77109191U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h__Script_SoftDesignTraining_2111061229(TEXT("/Script/SoftDesignTraining"),
	Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h__Script_SoftDesignTraining_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h__Script_SoftDesignTraining_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS

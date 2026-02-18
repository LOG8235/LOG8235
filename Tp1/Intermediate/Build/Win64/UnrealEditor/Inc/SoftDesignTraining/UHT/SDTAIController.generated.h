// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SDTAIController.h"

#ifdef SOFTDESIGNTRAINING_SDTAIController_generated_h
#error "SDTAIController.generated.h already included, missing '#pragma once' in SDTAIController.h"
#endif
#define SOFTDESIGNTRAINING_SDTAIController_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class ASDTAIController *********************************************************
SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTAIController_NoRegister();

#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASDTAIController(); \
	friend struct Z_Construct_UClass_ASDTAIController_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASDTAIController_NoRegister(); \
public: \
	DECLARE_CLASS2(ASDTAIController, AAIController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SoftDesignTraining"), Z_Construct_UClass_ASDTAIController_NoRegister) \
	DECLARE_SERIALIZER(ASDTAIController) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_16_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ASDTAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASDTAIController(ASDTAIController&&) = delete; \
	ASDTAIController(const ASDTAIController&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASDTAIController); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASDTAIController); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ASDTAIController) \
	NO_API virtual ~ASDTAIController();


#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_13_PROLOG
#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_16_INCLASS_NO_PURE_DECLS \
	FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASDTAIController;

// ********** End Class ASDTAIController ***********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SDTAIController_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS

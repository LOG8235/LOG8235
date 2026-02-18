// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "SoftDesignTrainingCharacter.h"

#ifdef SOFTDESIGNTRAINING_SoftDesignTrainingCharacter_generated_h
#error "SoftDesignTrainingCharacter.generated.h already included, missing '#pragma once' in SoftDesignTrainingCharacter.h"
#endif
#define SOFTDESIGNTRAINING_SoftDesignTrainingCharacter_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;
class UPrimitiveComponent;
struct FHitResult;

// ********** Begin Class ASoftDesignTrainingCharacter *********************************************
#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnBeginOverlap);


SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter_NoRegister();

#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesASoftDesignTrainingCharacter(); \
	friend struct Z_Construct_UClass_ASoftDesignTrainingCharacter_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend SOFTDESIGNTRAINING_API UClass* Z_Construct_UClass_ASoftDesignTrainingCharacter_NoRegister(); \
public: \
	DECLARE_CLASS2(ASoftDesignTrainingCharacter, ACharacter, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SoftDesignTraining"), Z_Construct_UClass_ASoftDesignTrainingCharacter_NoRegister) \
	DECLARE_SERIALIZER(ASoftDesignTrainingCharacter)


#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_ENHANCED_CONSTRUCTORS \
	/** Deleted move- and copy-constructors, should never be used */ \
	ASoftDesignTrainingCharacter(ASoftDesignTrainingCharacter&&) = delete; \
	ASoftDesignTrainingCharacter(const ASoftDesignTrainingCharacter&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ASoftDesignTrainingCharacter); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ASoftDesignTrainingCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ASoftDesignTrainingCharacter) \
	NO_API virtual ~ASoftDesignTrainingCharacter();


#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_7_PROLOG
#define FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_INCLASS_NO_PURE_DECLS \
	FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ASoftDesignTrainingCharacter;

// ********** End Class ASoftDesignTrainingCharacter ***********************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Ecole_Log_Log8235_Tp1_LOG8235_Source_SoftDesignTraining_SoftDesignTrainingCharacter_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS

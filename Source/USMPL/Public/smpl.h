// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#ifdef JULIA_DEFINE_FAST_TLS // only available in Julia v0.7 and above
JULIA_DEFINE_FAST_TLS()
#endif

#define JULIA_ENABLE_THREADING 0
// Julia headers (for initialization and gc commands)
#include "uv.h"
#include "julia.h"

#include "smpl.generated.h"

/**
 * 
 */
UCLASS()
class USMPL_API Usmpl : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
	// import functions from DLL
	static bool importDLL();
	static bool importMethodCSMPL();
	static bool importMethodCSMPL_v_template();
	static bool importMethodCSMPL_shapedirs();
	static bool importMethodCSMPL_posedirs();
	static bool importMethodCSMPL_J_regressor();
	static bool importMethodCSMPL_parents();
	static bool importMethodCSMPL_lbs_weights();
	static bool importMethodCSMPL_f();
	static bool importMethodCSMPL_LBS();
	static bool importMethodCSMPL_uv();

	// Module functions
	static jl_value_t* CSMPL();
	static jl_array_t* CSMPL_v_template(jl_array_t*);
	static jl_array_t* CSMPL_uv(jl_array_t*);
	static jl_array_t* CSMPL_shapedirs(jl_array_t*);
	static jl_array_t* CSMPL_posedirs(jl_array_t*);
	static jl_array_t* CSMPL_J_regressor(jl_array_t*);
	static jl_array_t* CSMPL_parents(jl_array_t*);
	static jl_array_t* CSMPL_lbs_weights(jl_array_t*);
	static jl_array_t* CSMPL_f(jl_array_t*);
	static jl_array_t* CSMPL_LBS(jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*);
	/*static jl_array_t* CSMPL_LBS(jl_value_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*,
		jl_array_t*);*/

		// Free DLL
	static void freeDLL();
	
};

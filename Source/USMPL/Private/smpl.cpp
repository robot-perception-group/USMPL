// Fill out your copyright notice in the Description page of Project Settings.

#include "smpl.h"
#include <iostream>

typedef jl_value_t*(*_CSMPL)();
typedef jl_array_t*(*_CSMPL_v_template)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_shapedirs)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_posedirs)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_J_regressor)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_parents)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_lbs_weights)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_f)(jl_array_t*);
//typedef jl_array_t*(*_CSMPL_uv)(jl_array_t*);
typedef jl_array_t*(*_CSMPL_LBS)(jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*);
/*
typedef jl_array_t*(*_CSMPL_LBS)(jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*,
	jl_value_t*);*/

_CSMPL						m_CSMPL;
_CSMPL_v_template			m_CSMPL_v_template;
_CSMPL_shapedirs			m_CSMPL_shapedirs;
_CSMPL_posedirs				m_CSMPL_posedirs;
_CSMPL_J_regressor			m_CSMPL_J_regressor;
_CSMPL_parents				m_CSMPL_parents;
_CSMPL_lbs_weights			m_CSMPL_lbs_weights;
_CSMPL_f					m_CSMPL_f;
_CSMPL_LBS					m_CSMPL_LBS;
//_CSMPL_uv					m_CSMPL_uv;

void *v_dllHandle;

/*
Usmpl::Usmpl()
{
	jl_init_with_image(NULL, "D:\\projects\\pyexp\\Binaries\\Win64\\SMPLMod.dll");
	jl_fl32_2_arr = jl_apply_array_type((jl_value_t*)jl_float32_type, 2);
	jl_fl32_3_arr = jl_apply_array_type((jl_value_t*)jl_float32_type, 3);
	jl_int64_2_arr = jl_apply_array_type((jl_value_t*)jl_int64_type, 2);
	jl_uint32_2_arr = jl_apply_array_type((jl_value_t*)jl_uint32_type, 2);

	v_template = jl_ptr_to_array(jl_fl32_2_arr, v_template_buf, (jl_value_t*)jl_eval_string("(6890,3)"), 0);
	shapedirs = jl_ptr_to_array(jl_fl32_3_arr, shapedirs_buf, (jl_value_t*)jl_eval_string("(6890,3,10)"), 0);
	posedirs = jl_ptr_to_array(jl_fl32_2_arr, posedirs_buf, (jl_value_t*)jl_eval_string("(207,20670)"), 0);
	J_regressor = jl_ptr_to_array(jl_fl32_2_arr, parents_buf, (jl_value_t*)jl_eval_string("(24,6890)"), 0);
	parents = jl_ptr_to_array(jl_int64_2_arr, parents_buf, (jl_value_t*)jl_eval_string("(24,)"), 0);
	lbs_weights = jl_ptr_to_array(jl_fl32_3_arr, lbs_weights_buf, (jl_value_t*)jl_eval_string("(6890,24)"), 0);
	f = jl_ptr_to_array(jl_uint32_2_arr, f_buf, (jl_value_t*)jl_eval_string("(13776,3)"), 0);
}*/


#pragma region Load DLL

// Method to import a DLL.
bool Usmpl::importDLL()
{
	//FString filePath = FGenericPlatformMisc::GetEnvironmentVariable("CSMPL_LIB_PATH");
	FString filePath = "C:\\Users\\nsaini\\Documents\\Unreal Projects\\SMPLPluginTest_18\\Binaries\\Win64\\csmpl.dll";

	if (FPaths::FileExists(*filePath))
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (v_dllHandle != NULL)
		{
			//UE_LOG(LogSMPL, Log, TEXT("SMPL module loaded"));
			return true;
		}
	}
	return false;	// Return an error.
}
#pragma endregion Load DLL



#pragma region Import Methods

// Imports the method getInvertedBool from the DLL.
bool Usmpl::importMethodCSMPL()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL = NULL;
		FString procName = "CSMPL";	// Needs to be the exact name of the DLL method.
		m_CSMPL = (_CSMPL)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_v_template()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_v_template = NULL;
		FString procName = "CSMPL_v_template";	// Needs to be the exact name of the DLL method.
		m_CSMPL_v_template = (_CSMPL_v_template)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_v_template != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_shapedirs()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_shapedirs = NULL;
		FString procName = "CSMPL_shapedirs";	// Needs to be the exact name of the DLL method.
		m_CSMPL_shapedirs = (_CSMPL_shapedirs)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_shapedirs != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_posedirs()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_posedirs = NULL;
		FString procName = "CSMPL_posedirs";	// Needs to be the exact name of the DLL method.
		m_CSMPL_posedirs = (_CSMPL_posedirs)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_posedirs != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_J_regressor()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_J_regressor = NULL;
		FString procName = "CSMPL_J_regressor";	// Needs to be the exact name of the DLL method.
		m_CSMPL_J_regressor = (_CSMPL_J_regressor)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_J_regressor != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_parents()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_parents = NULL;
		FString procName = "CSMPL_parents";	// Needs to be the exact name of the DLL method.
		m_CSMPL_parents = (_CSMPL_parents)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_parents != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_lbs_weights()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_lbs_weights = NULL;
		FString procName = "CSMPL_lbs_weights";	// Needs to be the exact name of the DLL method.
		m_CSMPL_lbs_weights = (_CSMPL_lbs_weights)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_lbs_weights != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
bool Usmpl::importMethodCSMPL_f()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_f = NULL;
		FString procName = "CSMPL_f";	// Needs to be the exact name of the DLL method.
		m_CSMPL_f = (_CSMPL_f)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_f != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}
/*
bool Usmpl::importMethodCSMPL_uv()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_uv = NULL;
		FString procName = "CSMPL_uv";	// Needs to be the exact name of the DLL method.
		m_CSMPL_uv = (_CSMPL_uv)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_uv != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}*/
bool Usmpl::importMethodCSMPL_LBS()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL_LBS = NULL;
		FString procName = "CSMPL_LBS";	// Needs to be the exact name of the DLL method.
		m_CSMPL_LBS = (_CSMPL_LBS)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CSMPL_LBS != NULL)
		{
			return true;
		}
	}
	return false;	// Return an error.
}


#pragma endregion Import Methods

#pragma region Method Calls

// Calls the method getInvertedBoolFromDll that was imported from the DLL.
jl_value_t*  Usmpl::CSMPL()
{
	//if (m_CSMPL_v_template != NULL)
	//{
	jl_value_t* vt = m_CSMPL(); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return vt;
	//}
	//return false;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_v_template(jl_array_t* v_template)
{
	//if (m_CSMPL_v_template != NULL)
	//{
	jl_array_t* vt = m_CSMPL_v_template(v_template); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return vt;
	//}
	//return false;	// Return an error.
}
/*
jl_array_t*  Usmpl::CSMPL_uv(jl_array_t* uv)
{
	//if (m_CSMPL_v_template != NULL)
	//{
	jl_array_t* u = m_CSMPL_uv(uv); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return u;
	//}
	//return false;	// Return an error.
}*/
jl_array_t*  Usmpl::CSMPL_shapedirs(jl_array_t* shapedir)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* shapedirs = m_CSMPL_shapedirs(shapedir); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.

	return shapedirs;
	//}
	//return npzfile;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_posedirs(jl_array_t* posedirs)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* posedir = m_CSMPL_posedirs(posedirs); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return posedir;
	//}
	//return npzfile;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_J_regressor(jl_array_t* J_regressor)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* J_regresso = m_CSMPL_J_regressor(J_regressor); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return J_regresso;
	//}
	//return npzfile;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_parents(jl_array_t* parents)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* parent = m_CSMPL_parents(parents); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return parent;
	//}
	//return npzfile;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_lbs_weights(jl_array_t* lbs_weights)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* lbs_weight = m_CSMPL_lbs_weights(lbs_weights); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return lbs_weight;
	//}
	//return npzfile;	// Return an error.
}
jl_array_t*  Usmpl::CSMPL_f(jl_array_t* f)
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* fr = m_CSMPL_f(f); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	return fr;
	//}
	//return npzfile;	// Return an error.
}


jl_array_t*  Usmpl::CSMPL_LBS(jl_array_t* v_template,
	jl_array_t* shapedirs,
	jl_array_t* posedirs,
	jl_array_t* J_regressor,
	jl_array_t* parents,
	jl_array_t* lbs_weights,
	jl_array_t* pose,
	jl_array_t* shape,
	jl_array_t* trans,
	jl_array_t* vposed)
	/*
	jl_array_t*  Usmpl::CSMPL_LBS(jl_value_t* smpl,
		jl_array_t* pose,
		jl_array_t* shape,
		jl_array_t* trans,
		jl_array_t* vposed)*/
{
	//if (m_CSMPL != NULL)
	//{
	jl_array_t* verts = m_CSMPL_LBS((jl_value_t*)v_template,
		(jl_value_t*)shapedirs,
		(jl_value_t*)posedirs,
		(jl_value_t*)J_regressor,
		(jl_value_t*)parents,
		(jl_value_t*)lbs_weights,
		(jl_value_t*)pose,
		(jl_value_t*)shape,
		(jl_value_t*)trans,
		(jl_value_t*)vposed);
	/*
	jl_array_t* verts = m_CSMPL_LBS(smpl,
		(jl_value_t*)pose,
		(jl_value_t*)shape,
		(jl_value_t*)trans,
		(jl_value_t*)vposed);
	*/
	return verts;

	//}
	//return npzfile;	// Return an error.
}


#pragma endregion Method Calls


#pragma region Unload DLL

// If you love something  set it free.
void Usmpl::freeDLL()
{
	if (v_dllHandle != NULL)
	{
		m_CSMPL = NULL;
		m_CSMPL_v_template = NULL;
		m_CSMPL_shapedirs = NULL;
		m_CSMPL_posedirs = NULL;
		m_CSMPL_J_regressor = NULL;
		m_CSMPL_parents = NULL;
		m_CSMPL_lbs_weights = NULL;
		m_CSMPL_f = NULL;
		m_CSMPL_LBS = NULL;
		//m_CSMPL_uv = NULL;
		FPlatformProcess::FreeDllHandle(v_dllHandle);
		v_dllHandle = NULL;
	}
}
#pragma endregion Unload DLL
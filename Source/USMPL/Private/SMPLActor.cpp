// Fill out your copyright notice in the Description page of Project Settings.


#include "SMPLActor.h"
#include <iostream>


// Sets default values
ASMPLActor::ASMPLActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SmplMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("SMPL"));
	RootComponent = SmplMesh;

	SmplMesh->bUseAsyncCooking = true;

	std::fill_n(pose_buf, 72, 0);
	std::fill_n(shape_buf, 10, 0);
	std::fill_n(trans_buf, 3, 0);
	std::fill_n(verts_buf, 6890 * 3, 0);

	FString csmpl_lib_path;
	for (uint32 Length = 128;;)
	{
		TArray<TCHAR>& CharArray = csmpl_lib_path.GetCharArray();
		CharArray.SetNumUninitialized(Length);

		Length = ::GetEnvironmentVariableW(TEXT("CSMPL_LIB_PATH"), CharArray.GetData(), CharArray.Num());
		if (Length == 0)
		{
			csmpl_lib_path.Reset();
			UE_LOG(LogTemp, Error, TEXT("CSMPL_LIB_PATH is not set"));
			break;
		}
		else if (Length < (uint32)CharArray.Num())
		{
			CharArray.SetNum(Length + 1);
			break;
		}
	}
	//jl_init_with_image(NULL, R"(C:\Users\nsaini\Desktop\projects\SMPL.jl\build\csmpl.dll)");
	jl_init_with_image(NULL, TCHAR_TO_ANSI(*csmpl_lib_path));
	
	jl_value_t* jl_fl32_1_arr = jl_apply_array_type((jl_value_t*)jl_float32_type, 1);
	jl_value_t* jl_fl32_2_arr = jl_apply_array_type((jl_value_t*)jl_float32_type, 2);
	jl_value_t* jl_fl32_3_arr = jl_apply_array_type((jl_value_t*)jl_float32_type, 3);
	jl_value_t* jl_uint32_2_arr = jl_apply_array_type((jl_value_t*)jl_uint32_type, 2);
	jl_value_t* jl_uint32_1_arr = jl_apply_array_type((jl_value_t*)jl_uint32_type, 1);

	v_template = jl_ptr_to_array(jl_fl32_2_arr, v_template_buf, (jl_value_t*)jl_eval_string("(6890,3)"), 0);
	//uv = jl_ptr_to_array(jl_fl32_2_arr, uv_buf, (jl_value_t*)jl_eval_string("(6890,2)"), 0);
	shapedirs = jl_ptr_to_array(jl_fl32_3_arr, shapedirs_buf, (jl_value_t*)jl_eval_string("(6890,3,10)"), 0);
	posedirs = jl_ptr_to_array(jl_fl32_2_arr, posedirs_buf, (jl_value_t*)jl_eval_string("(207,20670)"), 0);
	J_regressor = jl_ptr_to_array(jl_fl32_2_arr, J_regressor_buf, (jl_value_t*)jl_eval_string("(24,6890)"), 0);
	parents = jl_ptr_to_array_1d(jl_uint32_1_arr, parents_buf, 24, 0);
	lbs_weights = jl_ptr_to_array(jl_fl32_3_arr, lbs_weights_buf, (jl_value_t*)jl_eval_string("(6890,24)"), 0);
	f = jl_ptr_to_array(jl_uint32_2_arr, f_buf, (jl_value_t*)jl_eval_string("(13776,3)"), 0);
	pose = jl_ptr_to_array_1d(jl_fl32_1_arr, pose_buf, 72, 0);
	shape = jl_ptr_to_array_1d(jl_fl32_1_arr, shape_buf, 10, 0);
	trans = jl_ptr_to_array_1d(jl_fl32_1_arr, trans_buf, 3, 0);
	smpl_verts = jl_ptr_to_array(jl_fl32_2_arr, verts_buf, (jl_value_t*)jl_eval_string("(3,6890)"), 0);


	jl_gc_enable(0);
	bool dll = Usmpl::importDLL();
	bool csm = Usmpl::importMethodCSMPL();
	bool cvt = Usmpl::importMethodCSMPL_v_template();
	//bool cuv = Usmpl::importMethodCSMPL_uv();
	bool cs = Usmpl::importMethodCSMPL_shapedirs();
	bool cp = Usmpl::importMethodCSMPL_posedirs();
	bool cj = Usmpl::importMethodCSMPL_J_regressor();
	bool cpa = Usmpl::importMethodCSMPL_parents();
	bool cl = Usmpl::importMethodCSMPL_lbs_weights();
	bool cf = Usmpl::importMethodCSMPL_f();
	bool clb = Usmpl::importMethodCSMPL_LBS();

	jl_value_t* smpl = Usmpl::CSMPL();
	jl_array_t* smpl_v_template = Usmpl::CSMPL_v_template(v_template);
	//jl_array_t* smpl_uv = Usmpl::CSMPL_uv(uv);
	jl_array_t* smpl_shapedirs = Usmpl::CSMPL_shapedirs(shapedirs);
	jl_array_t* smpl_posedirs = Usmpl::CSMPL_posedirs(posedirs);
	jl_array_t* smpl_J_regressor = Usmpl::CSMPL_J_regressor(J_regressor);
	jl_array_t* smpl_lbs_weights = Usmpl::CSMPL_lbs_weights(lbs_weights);
	jl_array_t* smpl_f = Usmpl::CSMPL_f(f);
	jl_array_t* smpl_parents = Usmpl::CSMPL_parents(parents);
	jl_gc_enable(1);
	//JL_GC_PUSH6(&smpl_v_template,&smpl_shapedirs,&smpl_posedirs,&smpl_J_regressor,&smpl_parents,&smpl_lbs_weights);
	jl_gc_enable(0);

	double start = FPlatformTime::Seconds();

	jl_gc_enable(0);
	jl_array_t* vertis = Usmpl::CSMPL_LBS(v_template,
		shapedirs,
		posedirs,
		J_regressor,
		parents,
		lbs_weights,
		pose,
		shape,
		trans,
		smpl_verts);
	jl_gc_enable(1);

	double end = FPlatformTime::Seconds();
	UE_LOG(LogTemp, Warning, TEXT("SMPL LBS executed in %f seconds."), end - start);

	/*for (int i = 0; i < 6890; i++)
	{
		UV.Add(FVector2D(uv_buf[i],uv_buf[6890+i]));
	}*/

	GenerateSMPLMesh();

	SmplMesh->ContainsPhysicsTriMeshData(true);
	


	// New in UE 4.17, multi-threaded PhysX cooking.
	//SmplMesh->bUseAsyncCooking = true;
}

// Called when the game starts or when spawned
void ASMPLActor::BeginPlay()
{
	Super::BeginPlay();

	jl_gc_enable(0);
	jl_array_t* vertis = Usmpl::CSMPL_LBS(v_template,
		shapedirs,
		posedirs,
		J_regressor,
		parents,
		lbs_weights,
		pose,
		shape,
		trans,
		smpl_verts);
	jl_gc_enable(1);

	UProceduralMeshComponent* root = Cast<UProceduralMeshComponent>(RootComponent);

	CurrentActorLocation = GetActorLocation();

	PoseTopic = NewObject<UTopic>(UTopic::StaticClass());
	UROSIntegrationGameInstance* rosinst = Cast<UROSIntegrationGameInstance>(GetGameInstance());
	PoseTopic->Init(rosinst->ROSIntegrationCore, PoseTopicName, TEXT("std_msgs/Float32MultiArray"));

	std::function<void(TSharedPtr<FROSBaseMsg>)> SubscribeCallback = std::bind(&ASMPLActor::SubscribeCallbackImpl, this, std::placeholders::_1);
	PoseTopic->Subscribe(SubscribeCallback);

	//FRuntimeMeshDataRef rootdata = root->GetOrCreateRuntimeMesh()->GetRuntimeMeshData(); //Get the mesh data from the root mesh, technically superfluous and bypasses IsInGameThread check
}

void ASMPLActor::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V2);
	Triangles.Add(V3);

	/*const FVector Edge01 = Vertices[V2] - Vertices[V1];
	const FVector Edge02 = Vertices[V3] - Vertices[V1];

	Normals.Add((Edge02 ^ Edge01).GetSafeNormal());
	Normals.Add((Edge02 ^ Edge01).GetSafeNormal());
	Normals.Add((Edge02 ^ Edge01).GetSafeNormal());*/
}


void ASMPLActor::GenerateSMPLMesh()
{
	

	for (int i = 0; i < 6890; i++)
	{
		Vertices.Add(FVector(*(verts_buf + 3 * i)*100, *(verts_buf + 3 * i + 1)*100, *(verts_buf + 3 * i + 2)*100));
		VertexColors.Add(FColor::Black);
	}
	for (int i = 0; i < 13776; i++)
	{
		AddTriangle(*(f_buf + 3 * i + 2), *(f_buf + 3 * i + 1), *(f_buf + 3 * i));
	}

	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices,Triangles, UV,Normals,Tangents);

	SmplMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UV, VertexColors, Tangents, true);

	SmplMesh->AddCollisionConvexMesh(Vertices);
	SmplMesh->bUseComplexAsSimpleCollision = false;
	SmplMesh->bUseAsyncCooking = false;
	SmplMesh->SetMassOverrideInKg(NAME_None, 100.0f, true); //Make the spawned object lighter
	SmplMesh->SetSimulatePhysics(true);

}


// Called every frame
void ASMPLActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*for (int i = 0; i < 72; i++)
	{
		pose_buf[i] = std::fmod(pose_buf[i] + float(0.1), 2 * PI);
	}*/
	
	if (!bWritingPoseBuf)
	{
		jl_gc_enable(0);
		jl_array_t* vertis = Usmpl::CSMPL_LBS(v_template,
			shapedirs,
			posedirs,
			J_regressor,
			parents,
			lbs_weights,
			pose,
			shape,
			trans,
			smpl_verts);
		jl_gc_enable(1);

		for (int i = 0; i < 6890; i++)
		{
			Vertices[i].X = *(verts_buf + 3 * i) * 100;
			Vertices[i].Y = *(verts_buf + 3 * i + 1) * 100;
			Vertices[i].Z = *(verts_buf + 3 * i + 2) * 100;
		}

		FHitResult HitResult;
		if (SetActorLocation(CurrentActorLocation, false, &HitResult) == false)
		{
			// If the set function returned false something is blocking at that location. We can interrogate this result to determine details of this  
			// @See FHitResult for more information  
			if (HitResult.GetActor() != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot move object to location, blocked by %s"), *HitResult.GetActor()->GetName());
			}
		}
		SmplMesh->UpdateMeshSection_LinearColor(0, Vertices, Normals, TArray<FVector2D>(), VertexColors, Tangents);
	}
	
}


void ASMPLActor::SubscribeCallbackImpl(TSharedPtr<FROSBaseMsg> msg)
{
	auto Concrete = StaticCastSharedPtr<ROSMessages::std_msgs::Float32MultiArray>(msg);
	if (Concrete.IsValid())
	{
		//std::cout << "Subscriber listened: " << TCHAR_TO_UTF8(*(Concrete->_Data)) << std::endl;
		bWritingPoseBuf = true;
		
		for (int i = 0; i < 3; i++)
		{
			trans_buf[i] = (Concrete->data)[i];
		}
		/*CurrentActorLocation.X = 10*(Concrete->data)[0];
		CurrentActorLocation.Y = 10*(Concrete->data)[1];
		CurrentActorLocation.Z = 10*(Concrete->data)[2];*/
		for (int i = 3; i < 75; i++)
		{
			pose_buf[i-3] = (Concrete->data)[i];
		}
		bWritingPoseBuf = false;
		UE_LOG(LogTemp, Warning, TEXT("Incoming String was : %f"), (Concrete->data)[0]);
	}
	return;
}

/*void ASMPLActor::FinishDestroy()
{
	jl_atexit_hook(0);

}*/

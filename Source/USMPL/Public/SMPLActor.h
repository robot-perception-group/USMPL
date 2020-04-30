// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GameFramework/Actor.h"

//#include "RuntimeMeshComponent.h"
//#include "RuntimeMeshGenericVertex.h" //Used to create packed vertices
//#include "RuntimeMeshShapeGenerator.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegration/Classes/ROSIntegrationGameInstance.h"
#include "ROSIntegration/Public/std_msgs/Float32MultiArray.h"

#include "smpl.h"

#ifdef JULIA_DEFINE_FAST_TLS // only available in Julia v0.7 and above
JULIA_DEFINE_FAST_TLS()
#endif


#include "SMPLActor.generated.h"

UCLASS()
class USMPL_API ASMPLActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMPLActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString PoseTopicName;
		
	UProceduralMeshComponent* SmplMesh;


	/* The vertices of the mesh */
	TArray<FVector> Vertices;

	/* The UV values for Mesh */
	TArray<FVector2D> UV;

	/* The triangles of the mesh */
	TArray<int32> Triangles;

	/* The normals of the mesh */
	TArray<FVector> Normals;

	/* The tangents of the mesh */
	TArray<FProcMeshTangent> Tangents;

	TArray<FLinearColor> VertexColors;

	FVector CurrentActorLocation;

	/* Creates a triangle that connects the given vertices */
	void AddTriangle(int32 V1, int32 V2, int32 V3);

	void GenerateSMPLMesh();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float* v_template_buf = new float[6890 * 3];
	float* shapedirs_buf = new float[6890 * 3 * 10];
	float* posedirs_buf = new float[207 * 20670];
	float* J_regressor_buf = new float[24 * 6890];
	unsigned int* parents_buf = new unsigned int[24];
	float* lbs_weights_buf = new float[6890 * 24];
	unsigned int* f_buf = new unsigned int[13776 * 3];
	float* pose_buf = new float[72];
	float* shape_buf = new float[10];
	float* trans_buf = new float[3];
	float* verts_buf = new float[6890 * 3];
	float* uv_buf = new float[6890 * 2];

	bool bWritingPoseBuf = false;

	jl_array_t* v_template;
	jl_array_t* shapedirs;
	jl_array_t* posedirs;
	jl_array_t* J_regressor;
	jl_array_t* parents;
	jl_array_t* lbs_weights;
	jl_array_t* f;
	jl_array_t* pose;
	jl_array_t* shape;
	jl_array_t* trans;
	jl_array_t* smpl_verts;
	jl_array_t* uv;
	/*
	static jl_array_t* CSMPL(jl_array_t*);
	static void jl_atexit_hook(int);*/
	//virtual void FinishDestroy();

	class UTopic *PoseTopic;

	void SubscribeCallbackImpl(TSharedPtr<class FROSBaseMsg> msg);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Cloth.generated.h"

UCLASS()
class CLOTHSIMULATION_API ACloth : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloth();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class UProceduralMeshComponent* ProceduralMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Parameters")
		FVector QuadSize = FVector(0, 10, 10);
	// The width of the cloth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Parameters")
		int32 m_width = 10;
	// The height of the cloth
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Parameters")
		int32 m_height = 10;

	virtual void PostActorCreated() override; // fires when dragged into the world or after finished being spawned
	virtual void PostLoad() override; // fires when open the world

private:
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;

	void GenerateMesh();
	void AddTriangleMesh(FVector TopRight, FVector BottomRight, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent);
	void AddQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent);
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloth.h"
#include <vector>

// Sets default values
ACloth::ACloth()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	ProceduralMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACloth::BeginPlay()
{
	Super::BeginPlay();
	
	// triangle part 
}

void ACloth::PostActorCreated()
{
	Super::PostActorCreated();
	GenerateMesh();
}

void ACloth::PostLoad()
{
	Super::PostLoad();
	GenerateMesh();
}

void ACloth::GenerateMesh()
{
	// When you want to update your material in the world via variables.
	Vertices.Reset();
	Triangles.Reset();
	Normals.Reset();
	Tangents.Reset();
	UVs.Reset();
	Colors.Reset();

	// The building blocks for generating the mesh
	int32 TriangleIndexCount = 0;
	std::vector<FVector> DefinedShape;

	FProcMeshTangent TangentSetup = FProcMeshTangent(0.0f, 1.0f, 0.0f);
	int shapeIndexCount = 0;

	// front
	for (int width = 0; width < m_width; ++width)
	{
		for (int height = 0; height < m_height; ++height)
		{
			DefinedShape.push_back(FVector(QuadSize.X, (width * 2 * QuadSize.Y) + QuadSize.Y, -(height * 2 * QuadSize.Z) + QuadSize.Z));
			DefinedShape.push_back(FVector(QuadSize.X, (width * 2 * QuadSize.Y) + QuadSize.Y, -(height * 2 * QuadSize.Z) - QuadSize.Z));
			DefinedShape.push_back(FVector(QuadSize.X, (width * 2 * QuadSize.Y) - QuadSize.Y, -(height * 2 * QuadSize.Z) + QuadSize.Z));
			DefinedShape.push_back(FVector(QuadSize.X, (width * 2 * QuadSize.Y) - QuadSize.Y, -(height * 2 * QuadSize.Z) - QuadSize.Z));
			AddQuadMesh(DefinedShape[shapeIndexCount], DefinedShape[shapeIndexCount + 1], DefinedShape[shapeIndexCount + 2], DefinedShape[shapeIndexCount + 3], TriangleIndexCount, TangentSetup);
			shapeIndexCount += 4;
		}
	}



	//back

	TangentSetup = FProcMeshTangent(0.0f, -1.0f, 0.0f);
	for (int width = 0; width < m_width; ++width)
	{
		for (int height = 0; height < m_height; ++height)
		{
			DefinedShape.push_back(FVector(-QuadSize.X, (width * 2 * QuadSize.Y) - QuadSize.Y, -(height * 2 * QuadSize.Z) + QuadSize.Z));
			DefinedShape.push_back(FVector(-QuadSize.X, (width * 2 * QuadSize.Y) - QuadSize.Y, -(height * 2 * QuadSize.Z) - QuadSize.Z));
			DefinedShape.push_back(FVector(-QuadSize.X, (width * 2 * QuadSize.Y) + QuadSize.Y, -(height * 2 * QuadSize.Z) + QuadSize.Z));
			DefinedShape.push_back(FVector(-QuadSize.X, (width * 2 * QuadSize.Y) + QuadSize.Y, -(height * 2 * QuadSize.Z) - QuadSize.Z));
			AddQuadMesh(DefinedShape[shapeIndexCount], DefinedShape[shapeIndexCount + 1], DefinedShape[shapeIndexCount + 2], DefinedShape[shapeIndexCount + 3], TriangleIndexCount, TangentSetup);
			shapeIndexCount += 4;
		}
	}

	ProceduralMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
}

void ACloth::AddTriangleMesh(FVector TopRight, FVector BottomRight, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent)

{

	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(BottomLeft);

	// Order does matter
	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	// Unreal gives us a handy feature for normals.

	FVector thisNorm = FVector::CrossProduct(TopRight, BottomRight).GetSafeNormal();

	for (int i = 0; i < 3; i++)

	{

		Normals.Add(thisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}



	UVs.Add(FVector2D(0.0f, 1.0f)); //Top Left
	UVs.Add(FVector2D(0.0f, 0.0f)); // Bottom Left
	UVs.Add(FVector2D(1.0f, 0.0f)); // Bottom Right

}

void ACloth::AddQuadMesh(FVector TopRight, FVector BottomRight, FVector TopLeft, FVector BottomLeft, int32& TriIndex, FProcMeshTangent Tangent)
{
	int32 Point1 = TriIndex++;
	int32 Point2 = TriIndex++;
	int32 Point3 = TriIndex++;
	int32 Point4 = TriIndex++;

	Vertices.Add(TopRight);
	Vertices.Add(BottomRight);
	Vertices.Add(TopLeft);
	Vertices.Add(BottomLeft);

	// Order does matter
	Triangles.Add(Point1);
	Triangles.Add(Point2);
	Triangles.Add(Point3);

	Triangles.Add(Point4);
	Triangles.Add(Point3);
	Triangles.Add(Point2);

	// Unreal gives us a handy feature for normals.
	FVector thisNorm = FVector::CrossProduct(TopLeft - BottomRight, TopLeft - TopRight).GetSafeNormal();
	for (int i = 0; i < 4; i++)
	{
		Normals.Add(thisNorm);
		Tangents.Add(Tangent);
		Colors.Add(FLinearColor::Green);
	}

	UVs.Add(FVector2D(0.0f, 1.0f)); //Top Left
	UVs.Add(FVector2D(0.0f, 0.0f)); // Bottom Left
	UVs.Add(FVector2D(1.0f, 1.0f)); // Bottom Right
	UVs.Add(FVector2D(1.0f, 0.0f)); // Top Right
}

// Called every frame
void ACloth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


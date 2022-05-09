// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestParticle.generated.h"

UCLASS()
class CLOTHSIMULATION_API ATestParticle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestParticle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cloth Parameters")
		float simulateDelay = 0.5f;

private:
	float mass = 1.0f;
	FVector prevPosition;
	FVector acceleration = FVector(0.0f, 0.0f, 0.0f);
	FVector velocity = (GetActorLocation() - prevPosition);
	float damping = 0.99f;
	bool isFalling;

	FTimerHandle simulateTimerHandle;
	
	void AddForce(FVector force);
	void Simulate();
};

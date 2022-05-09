// Fill out your copyright notice in the Description page of Project Settings.


#include "TestParticle.h"

// Sets default values
ATestParticle::ATestParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATestParticle::BeginPlay()
{
	Super::BeginPlay();

	prevPosition = GetActorLocation();

	GetWorldTimerManager().SetTimer(simulateTimerHandle, this, &ATestParticle::Simulate, simulateDelay, true, 2.0f);

	// simulateTimerHandle.Invalidate(); in case it needs to stop in certain event
}

void ATestParticle::AddForce(FVector force)
{
	acceleration += force / mass;
}

void ATestParticle::Simulate()
{
	// apply force


	// gravity
    if (isFalling)
    {
        //add gravity force
        AddForce(FVector(0, 0, -500.0f) * mass);
        if (GetActorLocation().Z <= 30.0f)
        {
            isFalling = false;
        }
    }
    else
    {
        //add gravity force
        AddForce(FVector(0, 0, 500.0f) * mass);
        if (GetActorLocation().Z >= 300.0f)
        {
            isFalling = true;
        }
    }

    // Verlet intergration
    AddForce(-velocity * damping / mass);
	FVector currentPosition = GetActorLocation();
    SetActorLocation(((1.0f + damping) * currentPosition) - (damping * prevPosition) + (acceleration * simulateDelay * simulateDelay));
	prevPosition = currentPosition;
	acceleration = FVector(0.0f, 0.0f, 0.0f);
}



// Called every frame
void ATestParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// t0 do: grid of particles
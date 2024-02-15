// Fill out your copyright notice in the Description page of Project Settings.


#include "HarmfulFloor.h"

// Sets default values
AHarmfulFloor::AHarmfulFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHarmfulFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHarmfulFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// When Player collides, begin to increase their timer. Stop When exited.
void AHarmfulFloor::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AHarmfulFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// When the Player Collides, launch them.
void ABouncePad::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABouncePad::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}




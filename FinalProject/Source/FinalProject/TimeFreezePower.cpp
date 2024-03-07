// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeFreezePower.h"

// Sets default values
ATimeFreezePower::ATimeFreezePower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeFreezePower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeFreezePower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


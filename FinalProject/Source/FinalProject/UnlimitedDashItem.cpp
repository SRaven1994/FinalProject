// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlimitedDashItem.h"

// Sets default values
AUnlimitedDashItem::AUnlimitedDashItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUnlimitedDashItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUnlimitedDashItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


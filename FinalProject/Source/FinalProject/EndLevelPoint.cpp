// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelPoint.h"
#include "Components/BoxComponent.h"
#include "Player1.h"

// Sets default values
AEndLevelPoint::AEndLevelPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AEndLevelPoint::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelPoint::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AEndLevelPoint::OnOverlapEnd);
	
}

// Called every frame
void AEndLevelPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLevelPoint::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AEndLevelPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


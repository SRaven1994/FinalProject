// Fill out your copyright notice in the Description page of Project Settings.


#include "HarmfulFloor.h"
#include "Components/BoxComponent.h"
#include "Player1.h"

// Sets default values
AHarmfulFloor::AHarmfulFloor()
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
void AHarmfulFloor::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AHarmfulFloor::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AHarmfulFloor::OnOverlapEnd);
	
}

// Called every frame
void AHarmfulFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// When Player collides, increase their timer
void AHarmfulFloor::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char1 = Cast<APlayer1>(OtherActor);
		if (Char1)
		{
			Char1->PlayerIncreaseTime();
		}
	}
}

void AHarmfulFloor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


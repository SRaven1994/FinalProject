// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad.h"
#include "Player1.h"
#include "Components/SphereComponent.h"

// Sets default values
ABouncePad::ABouncePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	Stand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Stand"));
	Stand->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void ABouncePad::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ABouncePad::OnOverlapEnd);
	
}

// Called every frame
void ABouncePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// When the Player Collides, launch them.
void ABouncePad::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char1 = Cast<APlayer1>(OtherActor);
		if (Char1)
		{
			Char1->ForceJump();
		}
	}
}

void ABouncePad::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}




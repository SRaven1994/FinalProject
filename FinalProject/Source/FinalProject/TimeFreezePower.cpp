// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeFreezePower.h"
#include "Components/SphereComponent.h"
#include "Player1.h"
#include "Player2.h"

// Sets default values
ATimeFreezePower::ATimeFreezePower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	// Set rotation
	bRotate = true;

	RotationRate = 90;

}

// Called when the game starts or when spawned
void ATimeFreezePower::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ATimeFreezePower::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ATimeFreezePower::OnOverlapEnd);
	
}

// Called every frame
void ATimeFreezePower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate object
	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += RotationRate * DeltaTime;
		SetActorRotation(Rotation);
	}

}

// Collision functions
void ATimeFreezePower::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When either player collides with item, freeze their time
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char1 = Cast<APlayer1>(OtherActor);
			if (Char1)
			{
				Char1->PlayerFreezeTime();
				Destroy();
			}
	}
}

void ATimeFreezePower::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


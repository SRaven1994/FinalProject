// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlimitedDashItem.h"
#include "Player1.h"
#include "Components/SphereComponent.h"

// Sets default values
AUnlimitedDashItem::AUnlimitedDashItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	// Set rotation
	bRotate = true;

	RotationRate = 90;
}

// Called when the game starts or when spawned
void AUnlimitedDashItem::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AUnlimitedDashItem::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AUnlimitedDashItem::OnOverlapEnd);
	
}

// Called every frame
void AUnlimitedDashItem::Tick(float DeltaTime)
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

void AUnlimitedDashItem::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char1 = Cast<APlayer1>(OtherActor);
		if (Char1)
		{
			Char1->GainUnlimitedEnergy();
			Destroy();
		}
	}
}

void AUnlimitedDashItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


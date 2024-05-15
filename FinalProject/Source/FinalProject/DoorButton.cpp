// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorButton.h"
#include "Player1.h"
#include "Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorButton::ADoorButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ButtonPressed = false;
}

// Called when the game starts or when spawned
void ADoorButton::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoorButton::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADoorButton::OnOverlapEnd);
	
}

// Called every frame
void ADoorButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Character)
	{
		if (Character->IsInteracting == true)
		{
			if (Door)
			{
				Door->ActivateDoor();
				Character->IsInteracting = false;
				ButtonPressed = true;
			}
		}
	}

}

void ADoorButton::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (Cast<APlayer1>(OtherActor))
	{
		Character = Cast<APlayer1>(OtherActor);
		if (Character)
		{
			Character->CanPressButton = true;
		}
	}
}

void ADoorButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayer1>(OtherActor))
	{
		Character = Cast<APlayer1>(OtherActor);
		if (Character)
		{
			Character->CanPressButton = false;
			Character = nullptr;
		}
	}
}


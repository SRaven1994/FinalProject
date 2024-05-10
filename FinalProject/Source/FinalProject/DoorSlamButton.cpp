// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorSlamButton.h"
#include "Player1.h"
#include "Door.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoorSlamButton::ADoorSlamButton()
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
void ADoorSlamButton::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADoorSlamButton::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADoorSlamButton::OnOverlapEnd);
	
}

// Called every frame
void ADoorSlamButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorSlamButton::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<APlayer1>(OtherActor))
	{
		Character = Cast<APlayer1>(OtherActor);
		if (Character->PlayerSlamming == true && ButtonPressed == false)
		{
			Door->ActivateDoor();
			ButtonPressed = true;
		}
	}

}

void ADoorSlamButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

		if (Cast<APlayer1>(OtherActor))
	{
		Character = Cast<APlayer1>(OtherActor);
		if (Character)
		{
			Character = nullptr;
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructableObject.h"
#include "Components/BoxComponent.h"
#include "Player1.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestructableObject::ADestructableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Active = false;

}

// Called when the game starts or when spawned
void ADestructableObject::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADestructableObject::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADestructableObject::OnOverlapEnd);
	
}

// Called every frame
void ADestructableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active == true)
	{
		DestroyObject();
	}

}

void ADestructableObject::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When character collides with object, can destroy
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char = Cast<APlayer1>(OtherActor);
		if (Char)
		{
			Active = true;
		}
	}
}

void ADestructableObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// When character collides no longer with object, cannot destroy
	if (Cast<APlayer1>(OtherActor))
	{
		APlayer1* Char = Cast<APlayer1>(OtherActor);
		if (Char)
		{
			Active = true;
		}
	}
}

void ADestructableObject::DestroyObject()
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* MyPawn = MyController->GetPawn();
	APlayer1* Char = Cast<APlayer1>(MyPawn);
	if (Char != nullptr && Char->PlayerSlamming == true)
	{
		Destroy();
	}
}


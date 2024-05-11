// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevelPoint.h"
#include "Components/BoxComponent.h"
#include "Player1.h"
#include "FinalProjectGameModeBase.h"
#include "Kismet/GameplayStatics.h"

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

	PlayersEnter = 0;

	CompetitiveMode = false;
}

// Called when the game starts or when spawned
void AEndLevelPoint::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AEndLevelPoint::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AEndLevelPoint::OnOverlapEnd);

	AFinalProjectGameModeBase* GameMode = Cast<AFinalProjectGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode->CompetitiveMode == true)
	{
		CompetitiveMode = true;
	}
	
}

// Called every frame
void AEndLevelPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Game End on collision with both players have entered the boundary
void AEndLevelPoint::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayer1* Char1 = Cast<APlayer1>(OtherActor);
	if (Char1)
	{
		APlayerController* DisableControls = Cast<APlayerController>(Char1->GetController());
		if (DisableControls)
		{
			Char1->DisableInput(DisableControls);
		}
		PlayersEnter += 1;
		if (CompetitiveMode == true)
		{
			Char1->TimeEnd = true;
		}
		else
		{
			if (PlayersEnter == 2)
			{
				Char1->TimeEnd = true;
			}
		}

	}
}

void AEndLevelPoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayer1* Char1 = Cast<APlayer1>(OtherActor);
	if (Char1)
	{
		PlayersEnter -= 1;
	}
}


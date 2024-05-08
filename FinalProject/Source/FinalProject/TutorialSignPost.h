// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TutorialSignPost.generated.h"

UCLASS()
class FINALPROJECT_API ATutorialSignPost : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialSignPost();

	// Create mesh 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Stand;

	// Create Sign States

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool MovementSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool JumpingSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool UnlimitedDashSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool FreezeTimeSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool DecreaseTimeSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool HazardSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool SlammingSign;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool DoorButtonSign;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Signs, meta = (AllowPrivateAccess = "true"))
	bool DashSign;

	// Create sphere collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create collision functions
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

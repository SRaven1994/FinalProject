// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorButton.generated.h"

class APlayer1;
class ADoor;

UCLASS()
class FINALPROJECT_API ADoorButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorButton();

	APlayer1* Character = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Door, meta = (AllowPrivateAccess = "true"))
	ADoor* Door = nullptr;

	// Create mesh 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	// Create box collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionVolume;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ButtonState, meta = (AllowPrivateAccess = "true"))
	bool ButtonPressed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Create Collision Functions
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

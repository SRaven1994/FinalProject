// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeFreezePower.generated.h"

UCLASS()
class FINALPROJECT_API ATimeFreezePower : public AActor
{
	GENERATED_BODY()
	
public:	
	
	// Create Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	// Create is rotating
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotations, meta = (AllowPrivateAccess = "true"))
	bool bRotate;

	// Create rotation rate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Rotations, meta = (AllowPrivateAccess = "true"))
	float RotationRate;
	
	// Sets default values for this actor's properties
	ATimeFreezePower();

	// Create sphere collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* CollisionVolume;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

};

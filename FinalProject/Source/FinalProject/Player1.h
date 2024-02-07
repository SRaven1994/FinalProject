// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player1.generated.h"

UCLASS()
class FINALPROJECT_API APlayer1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer1();

	// Create Player Movements 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float JumpHeightVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float TurnAmount;

	// Create Camera
	UPROPERTY(EditAnywhere, BluePrintReadWrite, category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, category = "Camera")
	class UCameraComponent* FollowCamera;

	// Create Cooldown Mechanics
	int Jumptimer;
	bool StartJumpTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Create Player Movement Functions
	void PlayerJump();

	void PlayerMoveForward(float InputAxis);

	void PlayerMoveRight(float InputAxis);

};

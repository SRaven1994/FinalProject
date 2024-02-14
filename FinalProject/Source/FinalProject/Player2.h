// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Player2.generated.h"

UCLASS()
class FINALPROJECT_API APlayer2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer2();

	// Create Player Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float JumpHeightVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	float TurnAmount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Movement")
	bool CharJumped;

	// Create Cooldowns
	int JumpTimer;
	bool StartJumpTimer;

	// Create Camera
	UPROPERTY(EditAnywhere, BluePrintReadWrite, category = "Camera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, category = "Camera")
	class UCameraComponent* FollowCamera;

	// Create Inputs
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputMappingContext* DefaultMappingContext;

	// Create Jump Input
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* JumpAction;

	// Create Movement Input
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* MoveAction;

	// Create Dash Input
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* DashAction;

	// Create Special Move Input
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* SpecialAction;

	// Create Slam/Interact Input
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	//class UInputAction* SlamAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Create Player Movement Functions
	UFUNCTION(BlueprintCallable)
	void PlayerJump();

	UFUNCTION(BlueprintCallable)
	void PlayerMovement(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void PlayerDash();

	UFUNCTION(BlueprintCallable)
	void PlayerSlam();

	UFUNCTION(BlueprintCallable)
	void PlayerSpecial();

	// Create Timer Functions 
	UFUNCTION(BlueprintCallable)
	void PlayerFreezeTime();

	UFUNCTION(BlueprintCallable)
	void PlayerIncreaseTime();

};

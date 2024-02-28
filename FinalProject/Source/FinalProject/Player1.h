// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Player1.generated.h"

UCLASS()
class FINALPROJECT_API APlayer1 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer1();

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
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Create Mechanics
	UPROPERTY(EditAnywhere, BluePrintReadWrite, category = "Mechanics")
	bool PlayerSlamming;

	// Create Dash Energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	float DashEnergy;

	// Create Max Dash Energy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	float MaxDashEnergy;

	// Create Can Dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats, meta = (AllowPrivateAccess = "true"))
	bool CanDash;

	// Create start timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timers, meta = (AllowPrivateAccess = "true"))
	bool StartTimer;

	// Create milliseconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timers, meta = (AllowPrivateAccess = "true"))
	int Milliseconds;

	// Create seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timers, meta = (AllowPrivateAccess = "true"))
	int Seconds;

	// Create minutes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timers, meta = (AllowPrivateAccess = "true"))
	int Minutes;

	//Create Inputs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	// Create Jump Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	// Create Movement Input
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	// Create Dash Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DashAction;

	// Create Special Move Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SpecialAction;

	// Create Slam/Interact Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SlamAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Create force character jump function
	void ForceJump();

	// Create Player Movement Functions
	UFUNCTION(BlueprintCallable)
	void PlayerJump();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void PlayerStartDash();

	UFUNCTION(BlueprintCallable)
	void PlayerEndDash();

	UFUNCTION(BlueprintCallable)
	void PlayerSlam();

	UFUNCTION(BlueprintCallable)
	void PlayerSpecial();

	// Create Timer Functions 
	UFUNCTION(BlueprintCallable)
	void PlayerFreezeTime();

	UFUNCTION(BlueprintCallable)
	void PlayerDecreaseTime();

	void Timer();

	// Create Gain dash energy function
	void GainEnergy();


};

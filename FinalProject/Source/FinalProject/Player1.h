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
	bool TimeFrozen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeshCollsions, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CollisionVolume;

	// Create Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

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

	// Create time freeze timer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Timers, meta = (AllowPrivateAccess = "true"))
	int TimeFreezeTimer;

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

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Create force character jump function
	void ForceJump();

	// Create Player Movement/controls Functions
	UFUNCTION(BlueprintCallable)
	void PlayerJump();

	void Move(const FInputActionValue& Value);

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
	void PlayerIncreaseTime();

	void Timer();

	// Create Gain dash energy function
	void GainEnergy();

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};

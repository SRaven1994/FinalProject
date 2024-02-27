// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"


// Sets default values
APlayer1::APlayer1()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	JumpHeightVelocity = 500.0f;
	WalkSpeed = 100.0f;
	TurnAmount = 0.0;
	JumpTimer = 0;
	CharJumped = false;
	StartJumpTimer = false;

	PlayerTimer = 0.0;
	PlayerSlamming = false;

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->TargetOffset = FVector(0.f, 0.f, 100.f);
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bEnableCameraRotationLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void APlayer1::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Make Player Jump 
void APlayer1::PlayerJump()
{
	UE_LOG(LogTemp, Warning, TEXT("Jump"));
	LaunchCharacter(FVector(0, 0, JumpHeightVelocity), false, true);
}

// Move Player Forward or Backwards
void APlayer1::PlayerMovement(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Move"));
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

// Perform a Dash
void APlayer1::PlayerDash()
{
	UE_LOG(LogTemp, Warning, TEXT("Dash"));
}

// Perform a Slam
void APlayer1::PlayerSlam()
{
	UE_LOG(LogTemp, Warning, TEXT("Slam"));
}

// Perform Special ability
void APlayer1::PlayerSpecial()
{
	UE_LOG(LogTemp, Warning, TEXT("Special"));
}

// Freeze the Player timer, then unfreeze after awhile
void APlayer1::PlayerFreezeTime()
{
	
}

// Increase Player Timer
void APlayer1::PlayerIncreaseTime()
{
}

// Decrease Player Timer
void APlayer1::PlayerDecreaseTime()
{
}





// Fill out your copyright notice in the Description page of Project Settings.


#include "Player2.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
APlayer2::APlayer2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	JumpHeightVelocity = 500.0f;
	WalkSpeed = 100.0f;
	TurnAmount = 0.0;
	JumpTimer = 0;
	CharJumped = false;
	StartJumpTimer = false;

	Milliseconds = 0;
	Seconds = 0;
	Minutes = 0;
	TimeFrozen = false;
	TimeFreezeTimer = 0;

	PlayerSlamming = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

// Called when the game starts or when spawned
void APlayer2::BeginPlay()
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
void APlayer2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dash Energy Regeneration
	if (CanDash == true && DashEnergy < 1200)
	{
		DashEnergy += 10.0;
	}

	// Run timer, stop it once player collect freeze power and resume after awhile
	if (TimeFrozen == false)
	{
		Timer();
	}

	// Countdown for time frozen, after awhile unfreeze it
	if (TimeFreezeTimer == 0 && TimeFrozen == true)
	{
		TimeFrozen = false;
	}
	else if (TimeFrozen == true && TimeFreezeTimer != 0)
	{
		TimeFreezeTimer -= 1;
	}
}

// Called to bind functionality to input
void APlayer2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayer2::Move);

		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayer2::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayer2::PlayerJump);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayer2::PlayerStartDash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &APlayer2::PlayerEndDash);

		// Slam
		EnhancedInputComponent->BindAction(SlamAction, ETriggerEvent::Started, this, &APlayer2::PlayerSlam);
		EnhancedInputComponent->BindAction(SlamAction, ETriggerEvent::Completed, this, &APlayer2::PlayerSlam);

		// Special
		EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Started, this, &APlayer2::PlayerSpecial);
		EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Completed, this, &APlayer2::PlayerSpecial);
	}

}

void APlayer2::ForceJump()
{
	LaunchCharacter(FVector(0, 0, 1000), false, true);
}

// Make Player Jump 
void APlayer2::PlayerJump()
{
	LaunchCharacter(FVector(0, 0, JumpHeightVelocity), false, true);
}

void APlayer2::Move(const FInputActionValue& Value)
{
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

void APlayer2::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Dash Mechanics, gain energy after dashing
void APlayer2::PlayerStartDash()
{
	if (CanDash == true)
	{
		FRotator PlayerDirection = GetActorRotation();
		FVector PlayerLocation = GetActorForwardVector();
		LaunchCharacter(PlayerLocation * DashEnergy, 0, false);
		CanDash = false;
		DashEnergy = 0;
	}
}

void APlayer2::PlayerEndDash()
{
	CanDash = true;
}

// Perform a Slam
void APlayer2::PlayerSlam()
{

}

// Perform Special ability
void APlayer2::PlayerSpecial()
{

}

// Freeze the Player timer, then unfreeze after awhile
void APlayer2::PlayerFreezeTime()
{
	TimeFreezeTimer = 180;
	TimeFrozen = true;
}

// Increase Player Timer from colliding on a hazard
void APlayer2::PlayerIncreaseTime()
{
	Seconds += 10;
}

// Timer - on milliseconds equal to 60 increamnt second, if seconds equal 60, incremeant minutes
void APlayer2::Timer()
{
	if (Seconds <= 60)
	{
		Minutes += 1;
		Seconds = 0;
	}
	else if (Milliseconds <= 60)
	{
		Seconds += 1;
		Milliseconds = 0;
	}
	else
	{
		Milliseconds += 2;
	}
}

// Gain Energy
void APlayer2::GainEnergy()
{
	DashEnergy = 1150;
}







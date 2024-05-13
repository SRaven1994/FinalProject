// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Landscape.h"
#include "Platforms.h"
#include "HarmfulFloor.h"
#include "DoorSlamButton.h"
#include "TutorialSignPost.h"
#include "MovableObject.h"


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

	Milliseconds = 0;
	Seconds = 0;
	Minutes = 0;
	TimeFrozen = false;
	TimeFreezeTimer = 0;

	PlayerSlamming = false;
	SlamVelocity = -1000.0f;
	
	DashEnergy = 1200;
	MaxDashEnergy = 1200;
	CanDash = true;
	HasUnlimitedDash = false;
	UnlimitedDashTimer = 0;

	CanPressButton = false;
	IsInteracting = false;

	TimeEnd = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	CollisionVolume = GetCapsuleComponent();

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
	
	CollisionVolume->OnComponentHit.AddDynamic(this, &APlayer1::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &APlayer1::OnOverlapEnd);

}

// Called every frame
void APlayer1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Dash Energy Regeneration
	if (CanDash == true && DashEnergy < 1200)
	{
		DashEnergy += 10.0;
	}

	// Run timer, stop it once player collect freeze power and resume after awhile
	if (TimeFrozen == false || TimeEnd == false)
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

	// Countdown for Unlimited Dash, after awhile return back to limited
	if (UnlimitedDashTimer == 0 && HasUnlimitedDash == true)
	{
		HasUnlimitedDash = false;
	}
	else if (HasUnlimitedDash == true && UnlimitedDashTimer != 0)
	{
		UnlimitedDashTimer -= 1;
	}
	 
}

// Called to bind functionality to input
void APlayer1::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Move
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayer1::Move);

		// Jump
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayer1::PlayerJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayer1::PlayerJump);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayer1::PlayerStartDash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &APlayer1::PlayerEndDash);

		// Slam
		EnhancedInputComponent->BindAction(SlamAction, ETriggerEvent::Started, this, &APlayer1::PlayerSlam);
		EnhancedInputComponent->BindAction(SlamAction, ETriggerEvent::Completed, this, &APlayer1::PlayerSlam);

		// Special
		EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Started, this, &APlayer1::PlayerSpecial);
		EnhancedInputComponent->BindAction(SpecialAction, ETriggerEvent::Completed, this, &APlayer1::PlayerSpecial);
	}
}

void APlayer1::ForceJump()
{
	LaunchCharacter(FVector(0, 0, 1000), false, true);
}

// Make Player Jump 
void APlayer1::PlayerJump()
{
	if (CharJumped == false)
	{
		CharJumped = true;
		LaunchCharacter(FVector(0, 0, JumpHeightVelocity), false, true);
	}
}

void APlayer1::Move(const FInputActionValue& Value)
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

void APlayer1::Look(const FInputActionValue& Value)
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
void APlayer1::PlayerStartDash()
{
	if (CanDash == true && HasUnlimitedDash == true)
	{
		FRotator PlayerDirection = GetActorRotation();
		FVector PlayerLocation = GetActorForwardVector();
		LaunchCharacter(PlayerLocation * DashEnergy, 0, false);
		CanDash = false;
	}
	else if (CanDash == true)
	{
		FRotator PlayerDirection = GetActorRotation();
		FVector PlayerLocation = GetActorForwardVector();
		LaunchCharacter(PlayerLocation * DashEnergy, 0, false);
		CanDash = false;
		DashEnergy = 0;
	}
}

void APlayer1::PlayerEndDash()
{
	CanDash = true;
}

// Perform a Slam
void APlayer1::PlayerSlam()
{
	if (CharJumped == true && PlayerSlamming == false)
	{
		PlayerSlamming = true;
		LaunchCharacter(FVector(0, 0, SlamVelocity = -1000.0f), false, true);
	}
}

// Perform Special ability
void APlayer1::PlayerSpecial()
{
	if (CanPressButton == true)
	{
		IsInteracting = true;
	}
}

// Freeze the Player timer, then unfreeze after awhile
void APlayer1::PlayerFreezeTime()
{
	TimeFreezeTimer = 180;
	TimeFrozen = true;	
}

// Increase Player Timer from colliding on a hazard
void APlayer1::PlayerIncreaseTime()
{
	Seconds += 10;
}

// Decrease player timer from collecting item that decrease your time
void APlayer1::PlayerDecreaseTime()
{
	int MinuteSeconds = 60 * Minutes;
	MinuteSeconds += Seconds;
	MinuteSeconds -= 20;
	Minutes = MinuteSeconds / 60;
	Seconds = MinuteSeconds % 60;
}

// Get total time to use for display win results in competitive mode
int APlayer1::GetPlayerTotalTime()
{
	 int MinuteSeconds = 60 * Minutes;
	 MinuteSeconds += Seconds;
	 MinuteSeconds *= 60;
	 MinuteSeconds += Milliseconds;
	 return MinuteSeconds;
}

// Timer - on milliseconds equal to 60 increament second, if seconds equal 60, increament minutes
void APlayer1::Timer()
{
	if (Seconds >= 60)
	{
		Minutes += 1;
		Seconds = 0;
	}
	else if (Milliseconds >= 60)
	{
		Seconds += 1;
		Milliseconds = 0;
	}
	else
	{
		Milliseconds += 2;
	}
}

// Gain Unlimited Energy and begin countdown of the power
void APlayer1::GainUnlimitedEnergy()
{
	DashEnergy = 1190;
	HasUnlimitedDash = true;
	UnlimitedDashTimer = 180;
}

// Reset slam and jump states
void APlayer1::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ALandscape>() || OtherActor->IsA<APlatforms>() || OtherActor->IsA<ADoorSlamButton>() || OtherActor->IsA<AHarmfulFloor>() || 
		OtherActor->IsA<AMovableObject>() || OtherActor->IsA<ATutorialSignPost>())
	{
		CharJumped = false;
		PlayerSlamming = false;
	}
}

void APlayer1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}





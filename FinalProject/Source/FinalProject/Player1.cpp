// Fill out your copyright notice in the Description page of Project Settings.


#include "Player1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
	LaunchCharacter(FVector(0, 0, JumpHeightVelocity), false, true);
}

// Move Player Forward or Backwards
void APlayer1::PlayerMovementForward(float InputAxis)
{
	AddMovementInput(GetActorForwardVector(), InputAxis);
}

// Move Player Right or Left
void APlayer1::PlayerMovementRight(float InputAxis)
{
	TurnAmount += InputAxis;
	if (Controller != nullptr)
	{
		Controller->ClientSetRotation(FRotator(0.0f, TurnAmount, 0.0f));
	}
}

void APlayer1::PlayerDash()
{
}

void APlayer1::PlayerSlam()
{
}

void APlayer1::PlayerSpecial()
{
}

void APlayer1::PlayerFreezeTime()
{
}


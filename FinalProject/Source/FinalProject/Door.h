#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

UCLASS()

class FINALPROJECT_API ADoor : public AActor

{
	GENERATED_BODY()

public:
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


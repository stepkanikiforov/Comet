// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "CometGameMode.h"
#include "Kismet/GameplayStatics.h"

#include "SkyActor.generated.h"

UCLASS()
class COMET_API ASkyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float DeltaRotation = 0.05f;

	ACometGameMode* GameMode = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};

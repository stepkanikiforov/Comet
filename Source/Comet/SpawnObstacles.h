// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h" 

#include "ObstaclesActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "CometGameMode.h"
#include "Particles/ParticleSystemComponent.h"

#include "SpawnObstacles.generated.h"

UCLASS()
class COMET_API ASpawnObstacles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnObstacles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

private:
	UParticleSystemComponent* StarsParticles = nullptr;

	FVector SelfLocation;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AObstaclesActor> Asteroid;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AObstaclesActor> Satellite;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AObstaclesActor> Crystal;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AObstaclesActor> Effect;

	void SpawnObstacles();

	float SpawnTime = 0;
	float SpawnEffectPandoraTime = 0;

	float Border = 200;

	ACometGameMode* GameMode = nullptr;
};

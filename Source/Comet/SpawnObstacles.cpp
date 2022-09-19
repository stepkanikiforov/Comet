// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnObstacles.h"


// Sets default values
ASpawnObstacles::ASpawnObstacles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnObstacles::BeginPlay()
{
	Super::BeginPlay();

	StarsParticles = FindComponentByClass<UParticleSystemComponent>();

	GameMode = Cast<ACometGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	SelfLocation = this->GetActorLocation();
}


// Called every frame
void ASpawnObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (SpawnTime >= GameMode->GetObstaclesSpawnTime())
	{
		SpawnObstacles();
		SpawnTime = 0;
	}
	else
	{
		SpawnTime += DeltaTime;
		SpawnEffectPandoraTime += DeltaTime;
	}

	if (!(GameMode->bActivateParticles))
	{
		StarsParticles->SetVisibility(false);
	}
}


void ASpawnObstacles::SpawnObstacles()
{
	FVector Location = SelfLocation + FVector(0, FMath::RandRange(-Border, Border), FMath::RandRange(-Border, Border));

	if (GameMode->bProgressSatellite)
	{
		GetWorld()->SpawnActor<AObstaclesActor>(Satellite, Location, FRotator(0, 0, 0));
	}
	else if (GameMode->bProgressCrystal)
	{
		GetWorld()->SpawnActor<AObstaclesActor>(Crystal, Location, FRotator(0, 0, 0));
	}
	else
	{
		float LogNum = (-1) * UKismetMathLibrary::Loge(UKismetMathLibrary::RandomFloat());
		if (LogNum >= 3)
		{
			GetWorld()->SpawnActor<AObstaclesActor>(Crystal, Location, FRotator(0, 0, 0));
		}
		else if (LogNum < 3 && LogNum >= 2 && !GameMode->bProgress && SpawnEffectPandoraTime > 5)
		{
			GetWorld()->SpawnActor<AObstaclesActor>(Effect, Location, FRotator(0, 0, 0));
			SpawnEffectPandoraTime = 0;
		}
		else if (LogNum < 2 && LogNum >= 1)
		{
			GetWorld()->SpawnActor<AObstaclesActor>(Satellite, Location, FRotator(0, 0, 0));
		}
		else
		{
			GetWorld()->SpawnActor<AObstaclesActor>(Asteroid, Location, FRotator(0, 0, 0));
		}
	}
}



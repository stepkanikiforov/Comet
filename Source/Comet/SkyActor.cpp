// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyActor.h"

// Sets default values
ASkyActor::ASkyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void ASkyActor::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<ACometGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ASkyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GameMode->bMoveSky)
	{
		if (DeltaRotation >= 360.0f)
		{
			DeltaRotation = 0.0f;
		}
		this->SetActorRotation(FRotator(DeltaRotation, 0, 0));
		DeltaRotation += 0.05f;
	}

}


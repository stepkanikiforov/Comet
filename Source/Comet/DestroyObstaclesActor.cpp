// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyObstaclesActor.h"

// Sets default values
ADestroyObstaclesActor::ADestroyObstaclesActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void ADestroyObstaclesActor::BeginPlay()
{
	Super::BeginPlay();
	
	this->GetComponents(Piece);
	Forse();

	SetLifeSpan(1.5);
}

// Called every frame
void ADestroyObstaclesActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyObstaclesActor::Forse()
{
	for (int i = 0; i < Piece.Num(); i++) {
		Piece[i]->AddForce(FVector(1000000, 0, 0));
	}
}


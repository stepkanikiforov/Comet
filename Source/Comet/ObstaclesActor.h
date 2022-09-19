// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "DestroyObstaclesActor.h"
#include "CometGameMode.h"


#include "ObstaclesActor.generated.h"

UCLASS()
class COMET_API AObstaclesActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstaclesActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UStaticMeshComponent* Body = nullptr;

	USphereComponent* SphereCollision = nullptr;

	ACometGameMode* GameMode = nullptr;


	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	FString NameBody;


	float RandX;
	float RandY;
	float RandZ;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<ADestroyObstaclesActor> DestroyActor;

	
};

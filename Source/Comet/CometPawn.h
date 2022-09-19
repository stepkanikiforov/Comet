// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
//#include "CometGameMode.h"
#include "GameUI.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "CometPawn.generated.h"

UCLASS()
class COMET_API ACometPawn : public APawn
{
	GENERATED_BODY()

public:
	ACometPawn();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FVector2D StartLocation = FVector2D(0, 0);
	FVector2D FinishtLocation = FVector2D(0, 0);
	FVector2D Direction;
	FVector LocationToSet;
	float Speed;
	float Side = 200;

	void Touch();
	void TouchPreesed();
	void TouchReleased();

	void SideRotate();
	FVector2D SideRotateLocation = FVector2D(0, 0);
	float SideRotation;
	

	bool bMove = false;

	USceneComponent* Scene = nullptr;
	USkeletalMeshComponent* Body = nullptr;
	UWidgetComponent* Widget = nullptr;
	UParticleSystemComponent* PunchParticles = nullptr;

	void SetDirectionInput(int32 DirectionToSet);
	int32 DirectionInput = 1;

	void SetTextScoreToGameUI(FString TextToSet);
	void SetTextCrystalToGameUI(FString TextToSet);

	void EndVisibleScore();
	void EndVisibleCrystal();

	void SetVisibilityBody(bool bVisibility);

	void SetPunchParticles();

protected:
	virtual void BeginPlay() override;

	APlayerController* PlayerController = nullptr;

	//ACometGameMode* GameMode = nullptr;

	class UGameUI* GameUI = nullptr;
	TSubclassOf<UUserWidget> GameUIClass;

	FTimerHandle VisibleTimer;
	float VisibleTime = 0.4f;

	
};

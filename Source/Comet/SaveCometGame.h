// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveCometGame.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API USaveCometGame : public USaveGame
{
	GENERATED_BODY()

public:

	USaveCometGame();

	UPROPERTY(VisibleAnywhere)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere)
		uint32 UserIndex;

	UPROPERTY(VisibleAnywhere)
		int32 ScoreText;

	UPROPERTY(VisibleAnywhere)
		int32 CrystalText;

	UPROPERTY(VisibleAnywhere)
		int32 ChoosenSkin;

	UPROPERTY(VisibleAnywhere)
		bool PinkSkin;
	UPROPERTY(VisibleAnywhere)
		bool YellowSkin;
	UPROPERTY(VisibleAnywhere)
		bool PinkShop;
	UPROPERTY(VisibleAnywhere)
		bool YellowShop;
};

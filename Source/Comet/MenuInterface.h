// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class COMET_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetGameMenu() = 0;
	virtual void SetMainMenu() = 0;
	//virtual void SetPauseMenu() = 0;
	virtual void VolumeTrigger() = 0;
	virtual void SetShopMenu() = 0;
	virtual void SaveGame() = 0;

	virtual void BuyingPinkSkin() = 0;
	virtual void BuyingYellowSkin() = 0;
};

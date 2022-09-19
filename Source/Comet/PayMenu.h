// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"

#include "Kismet/GameplayStatics.h"
#include "CometGameInstance.h"

#include "PayMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API UPayMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Crystal;

	UPROPERTY(meta = (BindWidget))
		UImage* CheckBlue;
	UPROPERTY(meta = (BindWidget))
		UImage* CheckPink;
	UPROPERTY(meta = (BindWidget))
		UImage* CheckYellow;

	void SetVisibilityCheck(int32 WhatVisibbility);

	TArray<UImage*> CheckArray;

	UPROPERTY(meta = (BindWidget))
		UButton* BlueColorButton;
	UPROPERTY(meta = (BindWidget))
		UButton* PinkColorButton;
	UPROPERTY(meta = (BindWidget))
		UButton* YellowColorButton;


	UPROPERTY(meta = (BindWidget))
		UButton* BuyPinkButton;
	UPROPERTY(meta = (BindWidget))
		UButton* BuyYellowButton;

private:

	UCometGameInstance* GameInstance;

	UPROPERTY(meta = (BindWidget))
		UButton* ReturnButton;


	

	UFUNCTION()
		void MainMenu();

	UFUNCTION()
		void SetBlueSkin();
	UFUNCTION()
		void SetPinkSkin();
	UFUNCTION()
		void SetYellowSkin();

	UFUNCTION()
		void BuyPinkSkin();
	UFUNCTION()
		void BuyYellowSkin();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "CometGameInstance.h"

#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Crystal;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* RecordScore;

	

private:

	UCometGameInstance* GameInstance;

	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;

	UPROPERTY(meta = (BindWidget))
		UButton* VolumeButtonOn;

	UPROPERTY(meta = (BindWidget))
		UButton* VolumeButtonOff;

	UPROPERTY(meta = (BindWidget))
		UButton* ShopButton;

	UFUNCTION()
		void PlayGame();

	UFUNCTION()
		void Volume();

	UFUNCTION()
		void OpenShopMenu();

	UTexture2D* Texture;
};

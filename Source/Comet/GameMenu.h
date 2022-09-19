// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"


#include "GameMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API UGameMenu : public UMenuWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Crystal;

	
	UPROPERTY(meta = (BindWidget))
	UImage* AnimationEffectImage;

	UPROPERTY(meta = (BindWidget))
	UImage* CrystalEffect;

	UPROPERTY(meta = (BindWidget))
		UImage* AsteroidEffect;

	UPROPERTY(meta = (BindWidget))
		UImage* SatelliteEffect;

	UPROPERTY(meta = (BindWidget))
		UImage* SpeedEffect;

	UPROPERTY(meta = (BindWidget))
		UImage* ReversEffect;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* PandoraProgress;




//private:
//	UPROPERTY(meta = (BindWidget))
//	UButton* PauseButton;
//
//	UFUNCTION()
//	void OpenPauseMenu();
};

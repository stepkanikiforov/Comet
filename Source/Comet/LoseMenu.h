// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "LoseMenu.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API ULoseMenu : public UUserWidget
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
		UTextBlock* RecordScore;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* RecordCalculate;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* ScoreCalculate;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PlusScore;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* PlusRecord;

	UPROPERTY(meta = (BindWidget))
		UButton* RepeatButton;

	UPROPERTY(meta = (BindWidget))
		UButton* MainMenuButton;
private:


	UFUNCTION()
		void RepeatGame();

	UFUNCTION()
		void MainMenu();
};

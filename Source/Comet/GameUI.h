// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

#include "GameUI.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API UGameUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize();

public:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* DeltaScore;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DeltaCrystal;

};

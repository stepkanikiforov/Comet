// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CometGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API UCometGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UCometGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init();

	bool TriggerVolume = true;

	UPROPERTY(BlueprintReadOnly)
	int32 SkinColor = 1;

	bool PawnVisibility;
};

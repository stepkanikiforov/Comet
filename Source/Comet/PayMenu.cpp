// Fill out your copyright notice in the Description page of Project Settings.


#include "PayMenu.h"

bool UPayMenu::Initialize()
{
	bool Success = Super::Initialize(); //Инициализируем
	if (!Success) return false; // Проверка инициализации

	if (!ensure(ReturnButton != nullptr)) return false;
	ReturnButton->OnClicked.AddDynamic(this, &UPayMenu::MainMenu);

	if (!ensure(BlueColorButton != nullptr)) return false;
	BlueColorButton->OnClicked.AddDynamic(this, &UPayMenu::SetBlueSkin);
	if (!ensure(PinkColorButton != nullptr)) return false;
	PinkColorButton->OnClicked.AddDynamic(this, &UPayMenu::SetPinkSkin);
	if (!ensure(YellowColorButton != nullptr)) return false;
	YellowColorButton->OnClicked.AddDynamic(this, &UPayMenu::SetYellowSkin);
	
	if (!ensure(BuyPinkButton != nullptr)) return false;
	BuyPinkButton->OnClicked.AddDynamic(this, &UPayMenu::BuyPinkSkin);
	if (!ensure(BuyYellowButton != nullptr)) return false;
	BuyYellowButton->OnClicked.AddDynamic(this, &UPayMenu::BuyYellowSkin);

	GameInstance = Cast<UCometGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CheckArray.Add(CheckBlue);
	CheckArray.Add(CheckPink);
	CheckArray.Add(CheckYellow);

	return true;
}

void UPayMenu::MainMenu()
{
	this->RemoveFromViewport();

	if (MenuInterface != nullptr)
	{
		MenuInterface->SetMainMenu();
	}
}

void UPayMenu::SetBlueSkin()
{
	GameInstance->SkinColor = 1;
	SetVisibilityCheck(1);
	MenuInterface->SaveGame();
}

void UPayMenu::SetPinkSkin()
{
	GameInstance->SkinColor = 2;
	SetVisibilityCheck(2);
	MenuInterface->SaveGame();
}

void UPayMenu::SetYellowSkin()
{
	GameInstance->SkinColor = 3;
	SetVisibilityCheck(3);
	MenuInterface->SaveGame();
}

void UPayMenu::SetVisibilityCheck(int32 WhatVisibbility)
{
	for (int i = 0; i < CheckArray.Num(); i++)
	{
		if (i == WhatVisibbility - 1)
		{
			CheckArray[i]->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			CheckArray[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPayMenu::BuyPinkSkin()
{
	MenuInterface->BuyingPinkSkin();
}

void UPayMenu::BuyYellowSkin()
{
	MenuInterface->BuyingYellowSkin();
}
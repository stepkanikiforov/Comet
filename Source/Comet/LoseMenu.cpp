// Fill out your copyright notice in the Description page of Project Settings.


#include "LoseMenu.h"

bool ULoseMenu::Initialize()
{
	bool Success = Super::Initialize(); //Инициализируем
	if (!Success) return false; // Проверка инициализации

	if (!ensure(RepeatButton != nullptr)) return false;
	RepeatButton->OnClicked.AddDynamic(this, &ULoseMenu::RepeatGame);

	if (!ensure(MainMenuButton != nullptr)) return false;
	MainMenuButton->OnClicked.AddDynamic(this, &ULoseMenu::MainMenu);

	return true;
}

void ULoseMenu::RepeatGame()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Maps/GameLevel"), true);
}

void ULoseMenu::MainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("/Game/Maps/MenuLevel"), true);
}
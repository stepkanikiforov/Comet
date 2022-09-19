// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenu.h"

bool UPauseMenu::Initialize()
{
	bool Success = Super::Initialize(); //Инициализируем
	if (!Success) return false; // Проверка инициализации

	if (!ensure(ReturnButton != nullptr)) return false;
	ReturnButton->OnClicked.AddDynamic(this, &UPauseMenu::OpenGameMenu);

	return true;
}

void UPauseMenu::OpenGameMenu()
{
	this->RemoveFromViewport();

	if (MenuInterface != nullptr)
	{
		MenuInterface->SetGameMenu();
	}
}
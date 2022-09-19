// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMenu.h"

bool UGameMenu::Initialize()
{
	bool Success = Super::Initialize(); //Инициализируем
	if (!Success) return false; // Проверка инициализации

	//if (!ensure(PauseButton != nullptr)) return false;
	//PauseButton->OnClicked.AddDynamic(this, &UGameMenu::OpenPauseMenu);

	return true;
}

//void UGameMenu::OpenPauseMenu()
//{
//	this->RemoveFromViewport();
//
//	if (MenuInterface != nullptr)
//	{
//		MenuInterface->SetPauseMenu();
//	}
//}




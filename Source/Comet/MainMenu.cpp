// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize(); //Инициализируем
	if (!Success) return false; // Проверка инициализации

	if (!ensure(PlayButton != nullptr)) return false;
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::PlayGame);

	if (!ensure(VolumeButtonOn != nullptr)) return false;
	VolumeButtonOn->OnClicked.AddDynamic(this, &UMainMenu::Volume);

	if (!ensure(VolumeButtonOff != nullptr)) return false;
	VolumeButtonOff->OnClicked.AddDynamic(this, &UMainMenu::Volume);

	if (!ensure(ShopButton != nullptr)) return false;
	ShopButton->OnClicked.AddDynamic(this, &UMainMenu::OpenShopMenu);

	GameInstance = Cast<UCometGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (!ensure(GameInstance != nullptr)) return false;

	if (GameInstance->TriggerVolume)
	{
		VolumeButtonOn->SetVisibility(ESlateVisibility::Visible);
		VolumeButtonOff->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		VolumeButtonOn->SetVisibility(ESlateVisibility::Hidden);
		VolumeButtonOff->SetVisibility(ESlateVisibility::Visible);
	}

	return true;
}

void UMainMenu::PlayGame()
{
	this->RemoveFromViewport();

	UGameplayStatics::OpenLevel(this, FName("/Game/Maps/GameLevel"), true);
}

void UMainMenu::Volume()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->VolumeTrigger();
	}

	if (GameInstance->TriggerVolume)
	{
		VolumeButtonOn->SetVisibility(ESlateVisibility::Visible);
		VolumeButtonOff->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		VolumeButtonOn->SetVisibility(ESlateVisibility::Hidden);
		VolumeButtonOff->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMainMenu::OpenShopMenu()
{
	this->RemoveFromViewport();

	if (MenuInterface != nullptr)
	{
		MenuInterface->SetShopMenu();
	}
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveCometGame.h"

USaveCometGame::USaveCometGame()
{
	SaveSlotName = TEXT("Save");
	UserIndex = 0;

	ScoreText = 0;
	CrystalText = 0;
	ChoosenSkin = 1;
	PinkSkin = false;
	YellowSkin = false;
	PinkShop = true;
	YellowShop = true;
}
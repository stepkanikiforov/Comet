// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUI.h"

bool UGameUI::Initialize()
{
	bool Success = Super::Initialize(); //��������������
	if (!Success) return false; // �������� �������������

	return true;
}
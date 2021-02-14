// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainGameUI.h"

#include "Object/CharacterBase.h"
#include "Controller/LSHPlayerController.h"

#include "UI/InventoryUI.h"
#include "UI/StatBarUI.h"

void UMainGameUI::Init()
{
	if (InventoryUI)
	{
		InventoryUI->LSHPlayerController = this->LSHPlayerController;
		InventoryUI->Init();
	}

	if (StatBarUI)
	{
		StatBarUI->LSHPlayerController = this->LSHPlayerController;
		StatBarUI->Init();
	}
}

UMainGameUI::UMainGameUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StatBarUI.h"

#include "Controller/LSHPlayerController.h"
#include "Object/PlayerCharacter.h"

#include "Components/VerticalBox.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Components/VerticalBoxSlot.h"
#include "Components/OverlaySlot.h"

#include "Blueprint/WidgetTree.h"

void UStatBarUI::AddEvent()
{
	APlayerCharacter* Player = LSHPlayerController->GetPlayerInstance();
	if (Player != nullptr)
	{
		Player->ChangeHP.AddDynamic(this, &UStatBarUI::DelFunc_CharacterHPChanged);
		Player->ChangeMP.AddDynamic(this, &UStatBarUI::DelFunc_CharacterMPChanged);
	}
}

void UStatBarUI::DelFunc_CharacterHPChanged()
{
	APlayerCharacter* Player = LSHPlayerController->GetPlayerInstance();
	if (Player != nullptr)
	{
		FCharacterStat Stat = Player->CharacterStat;
		FString HP = FString::Printf(TEXT("%d / %d"), Stat.CurrentHP, Stat.MaxHP);
		float HPPercent = (float)(Stat.CurrentHP) / (float)(Stat.MaxHP);

		TextBlock_HP->SetText(FText::FromString(HP));
		ProgressBar_HPBar->SetPercent(HPPercent);
	}
}

void UStatBarUI::DelFunc_CharacterMPChanged()
{
	APlayerCharacter* Player = LSHPlayerController->GetPlayerInstance();
	if (Player != nullptr)
	{
		FCharacterStat Stat = Player->CharacterStat;
		FString MP = FString::Printf(TEXT("%d / %d"), Stat.CurrentMP, Stat.MaxMP);
		float MPPercent = (float)(Stat.CurrentMP) / (float)(Stat.MaxMP);

		TextBlock_MP->SetText(FText::FromString(MP));
		ProgressBar_MPBar->SetPercent(MPPercent);
	}
}

void UStatBarUI::Init()
{
	//Event 등록
	AddEvent();

	WidgetTree->RootWidget = Panel_VerticalBox;
	Panel_VerticalBox->AddChildToVerticalBox(Overlay_HP);
	Panel_VerticalBox->AddChildToVerticalBox(Overlay_MP);
	Overlay_HP->AddChildToOverlay(ProgressBar_HPBar);
	Overlay_MP->AddChildToOverlay(ProgressBar_MPBar);
	Overlay_HP->AddChildToOverlay(TextBlock_HP);
	Overlay_MP->AddChildToOverlay(TextBlock_MP);

	UVerticalBoxSlot* HPOverlay_Slot = Cast<UVerticalBoxSlot>(Overlay_HP->Slot);
	UVerticalBoxSlot* MPOverlay_Slot = Cast<UVerticalBoxSlot>(Overlay_MP->Slot);
	UOverlaySlot* HPBar_Slot = Cast<UOverlaySlot>(ProgressBar_HPBar->Slot);
	UOverlaySlot* MPBar_Slot = Cast<UOverlaySlot>(ProgressBar_MPBar->Slot);
	UOverlaySlot* HPText_Slot = Cast<UOverlaySlot>(TextBlock_HP->Slot);
	UOverlaySlot* MPText_Slot = Cast<UOverlaySlot>(TextBlock_MP->Slot);

	HPOverlay_Slot->SetSize(FSlateChildSize());	
	HPOverlay_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	HPOverlay_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	MPOverlay_Slot->SetSize(FSlateChildSize());
	MPOverlay_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	MPOverlay_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	HPBar_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	HPBar_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
	MPBar_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	MPBar_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	HPText_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	HPText_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	MPText_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	MPText_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
}

UStatBarUI::UStatBarUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EnemyStatBarUI.h"

#include "Object/Enemy.h"

#include "Components/VerticalBox.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Components/VerticalBoxSlot.h"
#include "Components/OverlaySlot.h"

#include "Blueprint/WidgetTree.h"

UEnemyStatBarUI::UEnemyStatBarUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UEnemyStatBarUI::DelFunc_EnemyHPChanged()
{
	if (Target != nullptr)
	{
		FCharacterStat Stat = Target->CharacterStat;
		FString HP = FString::Printf(TEXT("%d / %d"), Stat.CurrentHP, Stat.MaxHP);
		float HPPercent = (float)(Stat.CurrentHP) / (float)(Stat.MaxHP);

		TextBlock_HP->SetText(FText::FromString(HP));
		ProgressBar_HPBar->SetPercent(HPPercent);
	}
}

void UEnemyStatBarUI::DelFunc_EnemyMPChanged()
{
	if (Target != nullptr)
	{
		FCharacterStat Stat = Target->CharacterStat;
		FString MP = FString::Printf(TEXT("%d / %d"), Stat.CurrentMP, Stat.MaxMP);
		float MPPercent = (float)(Stat.CurrentMP) / (float)(Stat.MaxMP);

		//TextBlock_MP->SetText(FText::FromString(MP));
		//ProgressBar_MPBar->SetPercent(MPPercent);
	}
}

void UEnemyStatBarUI::AddEvent()
{
	if (Target != nullptr)
	{
		Target->ChangeHP.AddDynamic(this, &UEnemyStatBarUI::DelFunc_EnemyHPChanged);
		Target->ChangeMP.AddDynamic(this, &UEnemyStatBarUI::DelFunc_EnemyMPChanged);
	}
}

void UEnemyStatBarUI::Init()
{
	AddEvent();

	WidgetTree->RootWidget = Panel_VerticalBox;
	Panel_VerticalBox->AddChildToVerticalBox(Overlay_HP);
	Overlay_HP->AddChildToOverlay(ProgressBar_HPBar);
	Overlay_HP->AddChildToOverlay(TextBlock_HP);

	UVerticalBoxSlot* HPOverlay_Slot = Cast<UVerticalBoxSlot>(Overlay_HP->Slot);
	UOverlaySlot* HPBar_Slot = Cast<UOverlaySlot>(ProgressBar_HPBar->Slot);
	UOverlaySlot* HPText_Slot = Cast<UOverlaySlot>(TextBlock_HP->Slot);

	HPOverlay_Slot->SetSize(FSlateChildSize());
	HPOverlay_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	HPOverlay_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	HPBar_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	HPBar_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	HPText_Slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
	HPText_Slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);

	Target->SetHp(Target->GetHP());
}
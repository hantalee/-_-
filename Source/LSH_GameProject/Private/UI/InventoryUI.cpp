// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryUI.h"

#include "UI/SlotUI.h"
#include "Blueprint/WidgetTree.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "Controller/LSHPlayerController.h"
#include "Object/Inventory.h"

#include "Components/Image.h"

void UInventoryUI::DelFunc_UpdateItemSlot(FName ItemRowName, int Count, int SlotNum)
{
	UInventory* Inventory = LSHPlayerController->Inventory;

	//해당 데이터가 존재하는지 확인
	FItemData ItemData;
	if (Inventory->GetItemDataRow(ItemRowName, &ItemData) == false)
		return;

	Slots[SlotNum]->SetTexture(ItemData.Texture);
	Slots[SlotNum]->SetItemType(ItemData.Type);
	Slots[SlotNum]->IsUsed = true;
	Slots[SlotNum]->ChangeItemCount(Count);

	//슬롯을 비워야 하는지 확인
	int ItemCount = Slots[SlotNum]->GetItemCount();
	if (ItemCount < 1)
	{
		Slots[SlotNum]->SetSlotEmpty(Texture_DefaultIcon);
		Inventory->RemoveItem(SlotNum);
	}
}


void UInventoryUI::SwapSlot(int From, int To)
{
	USlotUI* FromSlot = Slots[From];
	USlotUI* ToSlot = Slots[To];

	UTexture2D* TempTexture = FromSlot->GetTexture();
	EItemType TempItempType = FromSlot->ItemType;
	int TempItemCount = FromSlot->GetItemCount();
	bool TempIsUsed = FromSlot->IsUsed;

	FromSlot->SetTexture(ToSlot->GetTexture());
	FromSlot->SetItemType(ToSlot->ItemType);
	FromSlot->SetItemCount(ToSlot->GetItemCount());
	FromSlot->IsUsed = ToSlot->IsUsed;

	ToSlot->SetTexture(TempTexture);
	ToSlot->SetItemType(TempItempType);
	ToSlot->SetItemCount(TempItemCount);
	ToSlot->IsUsed = TempIsUsed;
}

void UInventoryUI::Init()	
{
	UInventory* Inventory = LSHPlayerController->Inventory;
	Inventory->Delgate_UpdateSlot.BindUFunction(this, FName("DelFunc_UpdateItemSlot"));


	int DefaultSlotNum = VerticalCount * HorizontalCount;
	Slots.Init(nullptr, DefaultSlotNum);
	int SlotNum = 0;
	for (int Row = 0; Row < VerticalCount; ++Row)
	{
		for (int Column = 0; Column < HorizontalCount; ++Column)
		{
			USlotUI* NewSlot = CreateWidget<USlotUI>(LSHPlayerController, USlotUI::StaticClass());
			NewSlot->LSHPlayerController = this->LSHPlayerController;
			NewSlot->Init();
			NewSlot->SetSlotType(ESlotType::Slot_Item);
			NewSlot->SetSlotEmpty(Texture_DefaultIcon);
			NewSlot->SlotNum = SlotNum;
			SlotNum++;
			Slots[NewSlot->SlotNum] = NewSlot;

			UniformGridPanel_Panel->AddChildToUniformGrid(NewSlot, Row, Column);
			UUniformGridSlot* UniformSlot = Cast<UUniformGridSlot>(NewSlot->Slot);
			UniformSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			UniformSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
	}
}

UInventoryUI::UInventoryUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

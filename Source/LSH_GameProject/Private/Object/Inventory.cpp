// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Inventory.h"

#include "Object/CharacterBase.h"

#include "GameInstance/LSHGameInstance.h"

#include "Object/Item.h"
#include "Object/ConsumerItem.h"
#include "Object/EquipItem.h"

void UInventory::Init(ACharacterBase* Target)
{
	User = Target;

	ItemList.Init(NAME_None, DefaultSlotNum);
	ItemObjectList.Init(nullptr, DefaultSlotNum);
}

bool UInventory::AddItem(FName ItemRowName, int Count)
{
	//해당 데이터가 존재하는지 확인
	FItemData ItemData;
	if (GetItemDataRow(ItemRowName, &ItemData) == false)
		return false;

	//인벤토리가 가득 찼다면
	if (IsInventoryFull())
		return false;

	int SlotNum = IsContains(ItemRowName);

	//인벤토리에 없는 아이템
	if (SlotNum == -1)
	{
		for (int i = 0; i < ItemList.Num(); ++i)
		{
			//해당 슬롯을 미사용 중이라면
			if (ItemList[i] == NAME_None)
			{
				ItemList[i] = ItemRowName;
				ItemObjectList[i] = AddItemByItemData(ItemData);
				SlotNum = i;
				break;
			}
		}
	}

	if (Delgate_UpdateSlot.IsBound())
		Delgate_UpdateSlot.Execute(ItemRowName, Count, SlotNum);

	return true;
}

void UInventory::RemoveItem(int SlotNum)
{
	ItemList[SlotNum] = NAME_None;
	ItemObjectList[SlotNum] = nullptr;
}

void UInventory::UsedItem(int SlotNum, EItemType Type)
{
	if (ItemObjectList[SlotNum] == nullptr)
		return;

	UItem* Item = ItemObjectList[SlotNum];
	bool Success;
	if (Type == Item_Equipment)
	{
		UEquipItem* EquipItem = Cast<UEquipItem>(Item);
		if(EquipItem->IsUsed == false)
			User->EquipItem(EquipItem);
	}
	else if (Type == Item_Useable)
	{
		Success = Item->Use(User);
		if (Success)
		{
			if (Delgate_UpdateSlot.IsBound())
				Delgate_UpdateSlot.Execute(ItemList[SlotNum], -1, SlotNum);
		}
	}
}

UItem* UInventory::AddItemByItemData(FItemData ItemData)
{
	ULSHGameInstance* GameInst = GetWorld()->GetGameInstance<ULSHGameInstance>();
	ensure(GameInst);
	if (!GameInst)
		return false;

	EItemType ItemType = ItemData.Type;
	FName ItemId = ItemData.Id;

	UDataTable* ItemTable = GameInst->GetDataTableByItemType(ItemType);
	ensure(ItemTable);
	if (!IsValid(ItemTable))
		return false;

	FString Context;
	switch (ItemType)
	{
		case Item_None:
			break;
		case Item_Useable:
		{
			FConsumerItemDataRow* Row = ItemTable->FindRow<FConsumerItemDataRow>(ItemId, Context);
			if (Row == nullptr)
				return nullptr;

			UConsumerItem* Item = NewObject<UConsumerItem>(this, UConsumerItem::StaticClass());

			Item->SetConsumerItemDataRow(*Row);
			return Item;
			break;
		}
		case Item_Equipment:
		{
			FEquipmentItemDataRow* Row = ItemTable->FindRow<FEquipmentItemDataRow>(ItemId, Context);
			if (Row == nullptr)
				return nullptr;

			UEquipItem* Item = NewObject<UEquipItem>(this, UEquipItem::StaticClass());
			Item->SetEquipmentItemDataRow(*Row);
			return Item;
			break;
		}
		default:
			break;
	}

	return nullptr;
}

int UInventory::IsContains(FName ItemName)
{
	for (int SlotNum = 0; SlotNum < ItemList.Num(); ++SlotNum)
	{
		if (ItemList[SlotNum] == ItemName)
		{
			return SlotNum;
		}
	}
	return -1;
}

bool UInventory::IsInventoryFull()
{
	int Count = 0;
	for (int i = 0; i < ItemList.Num(); ++i)
	{
		if (ItemList[i] != NAME_None)
			Count += 1;
	}

	if (ItemList.Num() <= Count)
		return true;

	return false;
}

bool UInventory::GetItemDataRow(FName InRowName, FItemData* ItemData)
{
	ULSHGameInstance* GameInst = GetWorld()->GetGameInstance<ULSHGameInstance>();
	ensure(GameInst);
	if (!GameInst)
		return false;

	UDataTable* ItemTable = GameInst->GetItemDataTable();

	ensure(ItemTable);
	if (!IsValid(ItemTable))
		return false;

	FString Context;
	FItemData* Row = ItemTable->FindRow<FItemData>(InRowName, Context);
	if (Row == nullptr)
		return false;

	*ItemData = *Row; //###얕은 복사 확인 해봐야함 2020.07.21
	return true;
}

UInventory::UInventory()
{

}

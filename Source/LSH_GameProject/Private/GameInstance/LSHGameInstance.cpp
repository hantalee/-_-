// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/LSHGameInstance.h"

#include "Object/Weapon.h"
#include "Object/EquipItem.h"

bool ULSHGameInstance::GetEquipmentDataRow(FName InRowName, FEquipmentItemDataRow* OutWeapon)
{
	ensure(IsValid(EquipmentItemDataTable));

	if (IsValid(EquipmentItemDataTable) == false)
		return false;

	FString Context;
	FEquipmentItemDataRow* Row = EquipmentItemDataTable->FindRow<FEquipmentItemDataRow>(InRowName, Context);
	if (Row == nullptr)
		return false;
	*OutWeapon = *Row;
	return true;
}

AWeapon* ULSHGameInstance::SpawnEquipmentItem(struct FEquipmentItemDataRow ItemRow, const FTransform& SpawnTransform, const FActorSpawnParameters& Params)
{
	ensure(IsValid(ItemRow.EquipmentActorClass));

	AWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AWeapon>(ItemRow.EquipmentActorClass, SpawnTransform, Params);
	SpawnedWeapon->Data = ItemRow;

	return SpawnedWeapon;	
}

UDataTable* ULSHGameInstance::GetDataTableByItemType(EItemType Type)
{
	switch (Type)
	{
	case Item_None:
		break;
	case Item_Useable:
	{
		return GetConsumerItemDataTable();
		break;
	}
	case Item_Equipment:
	{
		return GetEquipmentItemDataTable();
		break;
	}
	default:
		break;
	}

	return nullptr;
}

void ULSHGameInstance::OnStart()
{
	Super::OnStart();

	//ItemData
	ensure(IsValid(ItemDataTable));
	if (IsValid(ItemDataTable))
		ItemRowNames = ItemDataTable->GetRowNames();

	//EquipmentItem
	ensure(IsValid(EquipmentItemDataTable));
	if (IsValid(EquipmentItemDataTable))
		EquipmentItemRowNames = EquipmentItemDataTable->GetRowNames();

	//ConsumerItem
	ensure(IsValid(ConsumerItemDataTable));
	if (IsValid(ConsumerItemDataTable))
		ConsumerItemRowNames = ConsumerItemDataTable->GetRowNames();

	//CharacterStat
	ensure(IsValid(CharacterStatDataTable));
	if (IsValid(CharacterStatDataTable))
		CharacterStatRowNames = CharacterStatDataTable->GetRowNames();
}

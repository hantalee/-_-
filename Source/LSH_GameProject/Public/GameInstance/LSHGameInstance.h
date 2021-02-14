// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/GameInstance.h"
#include "Object/Inventory.h"
#include "Engine/DataTable.h"
#include "LSHGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LSH_GAMEPROJECT_API ULSHGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UDataTable* ItemDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UDataTable* EquipmentItemDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UDataTable* ConsumerItemDataTable;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UDataTable* CharacterStatDataTable;

	TArray<FName> ItemRowNames;
	TArray<FName> EquipmentItemRowNames;
	TArray<FName> ConsumerItemRowNames;
	TArray<FName> CharacterStatRowNames;

public:
	bool GetEquipmentDataRow(FName InRowName, struct FEquipmentItemDataRow* OutWeapon);
	class AWeapon* SpawnEquipmentItem(
		struct FEquipmentItemDataRow ItemRowName,
		const FTransform& SpawnTransform,
		const FActorSpawnParameters& Params = FActorSpawnParameters()
	);

	UDataTable* GetDataTableByItemType(EItemType Type);

protected:
	virtual void OnStart() override;

public:
	FORCEINLINE UDataTable* GetItemDataTable() const { return ItemDataTable; }
	FORCEINLINE TArray<FName> GetItemRowNames() const { return ItemRowNames; }

	FORCEINLINE UDataTable* GetEquipmentItemDataTable() const { return EquipmentItemDataTable; }
	FORCEINLINE TArray<FName> GetEquipmentItemRowNames() const { return EquipmentItemRowNames; }

	FORCEINLINE UDataTable* GetConsumerItemDataTable() const { return ConsumerItemDataTable; }
	FORCEINLINE TArray<FName> GetConsumerItemRowNames() const { return ConsumerItemRowNames; }

	FORCEINLINE UDataTable* GetCharacterStatDataTable() const { return CharacterStatDataTable; }
};

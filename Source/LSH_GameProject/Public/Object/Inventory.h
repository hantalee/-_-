// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Inventory.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum EItemType
{
	Item_None		UMETA(DisplayName = "None"),
	Item_Useable	UMETA(DisplayName = "Useable"),
	Item_Equipment	UMETA(DisplayName = "Equipment")
};

class UTexture2D;
USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Id = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name = NAME_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> Type = Item_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture; //###얕은 복사 확인 해봐야함 2020.07.21
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxCount = 999;
};


DECLARE_DELEGATE_ThreeParams(FUpdateSlot, FName, int, int);

class UItem;
class ACharacterBase;

UCLASS()
class LSH_GAMEPROJECT_API UInventory : public UObject
{
	GENERATED_BODY()
private:
	ACharacterBase* User;
public:
	UPROPERTY(EditAnywhere)
		int DefaultSlotNum = 10;
	UPROPERTY(VisibleAnywhere)
		TArray<FName> ItemList;
	UPROPERTY(VisibleAnywhere)
		TArray<UItem*> ItemObjectList;
public:
	//Delegate
	FUpdateSlot Delgate_UpdateSlot;
public:
	void Init(ACharacterBase* Target);
	bool AddItem(FName ItemRowName, int Count);
	void RemoveItem(int SlotNum);
	void UsedItem(int SlotNum, EItemType Type);
	UItem* AddItemByItemData(FItemData ItemData);

	int IsContains(FName ItemName);
	bool IsInventoryFull();
	bool GetItemDataRow(FName InRowName, FItemData* ItemData);
public:
	UInventory();
public:
	FORCEINLINE void SetInventoryUser(ACharacterBase* Target) { User = Target; }
	FORCEINLINE const ACharacterBase* GetInventoryUser() { return User; }
};

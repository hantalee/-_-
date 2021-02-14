// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Item.h"
#include "EquipItem.generated.h"

/**
 * 
 */
class AWeapon;

USTRUCT(BlueprintType)
struct FEquipmentItemDataRow : public FItemDataInfoRow
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AttackPower = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EquipmentActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;
};

UCLASS()
class LSH_GAMEPROJECT_API UEquipItem : public UItem
{
	GENERATED_BODY()

private:
	UPROPERTY()
		FEquipmentItemDataRow ItemDataRow;
public:
	bool IsUsed = false;
public:
	UEquipItem();
public:
	virtual bool Use(ACharacterBase* Target) override;
public:
	FORCEINLINE void SetEquipmentItemDataRow(FEquipmentItemDataRow DataTable) { ItemDataRow = DataTable; }
	FORCEINLINE FEquipmentItemDataRow GetEquipmentItemDataRow() { return ItemDataRow; }
};

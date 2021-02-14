// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/Item.h"
#include "ConsumerItem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum EConsumType
{
	Consum_None		UMETA(DisplayName = "None"),
	Consum_HP		UMETA(DisplayName = "HP"),
	Consum_MP		UMETA(DisplayName = "MP")
};

USTRUCT(BlueprintType)
struct FConsumerItemDataRow :public FItemDataInfoRow
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<EConsumType> Type = Consum_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Amount = 0;
};

UCLASS()
class LSH_GAMEPROJECT_API UConsumerItem : public UItem
{
	GENERATED_BODY()
private:
	UPROPERTY()
		TEnumAsByte<EConsumType> ConsumType;
	UPROPERTY()
		int ConsumAmount;
	UPROPERTY()
		FConsumerItemDataRow ItemDataRow;
public:
	UConsumerItem();
public:
	virtual bool Use(ACharacterBase* Target) override;
public:
	FORCEINLINE void SetConsumItemType(EConsumType Type) { ConsumType = Type; }
	FORCEINLINE const EConsumType GetConsumItemType() { return ConsumType; }

	FORCEINLINE void SetConsumItemAmount(int Amount) { ConsumAmount = Amount; }
	FORCEINLINE const int GetConsumItemAmount() { return ConsumAmount; }

	FORCEINLINE void SetConsumerItemDataRow(FConsumerItemDataRow DataTable) { ItemDataRow = DataTable; }
	FORCEINLINE FConsumerItemDataRow GetConsumerItemDataRow() { return ItemDataRow; }
};

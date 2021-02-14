// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
class ACharacterBase;

USTRUCT(BlueprintType)
struct FItemDataInfoRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;
};

UCLASS(abstract)
class LSH_GAMEPROJECT_API UItem : public UObject
{
	GENERATED_BODY()
private:
	ACharacterBase* Character;
public:
	UItem();
public:
	virtual bool Use(ACharacterBase* Target);

};

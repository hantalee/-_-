// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "UI/SlotUI.h"
#include "SlotDrag.generated.h"

/**
 * 
 */
enum ESlotType;

UCLASS()
class LSH_GAMEPROJECT_API USlotDrag : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int FromNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESlotType> SlotType;
};

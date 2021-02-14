// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "InventoryUI.generated.h"

/**
 * 
 */
class USlotUI;
class UUniformGridPanel;

UCLASS()
class LSH_GAMEPROJECT_API UInventoryUI : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UUniformGridPanel* UniformGridPanel_Panel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture_DefaultIcon;
	UPROPERTY(VisibleAnywhere)
		TArray<USlotUI*> Slots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int HorizontalCount = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int VerticalCount = 2;

public:
	UFUNCTION()
		void DelFunc_UpdateItemSlot(FName ItemName, int Count, int SlotNum);

	void SwapSlot(int From, int To);
public:
	virtual void Init() override;
public:
	UInventoryUI(const FObjectInitializer& ObjectInitializer);
};

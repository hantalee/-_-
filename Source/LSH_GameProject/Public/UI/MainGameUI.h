// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "MainGameUI.generated.h"

/**
 * 
 */
class UInventoryUI;
class UStatBarUI;

UCLASS()
class LSH_GAMEPROJECT_API UMainGameUI : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		UInventoryUI* InventoryUI;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
		UStatBarUI* StatBarUI;
public:
	virtual void Init() override;
public:
	UMainGameUI(const FObjectInitializer& ObjectInitializer);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
class ALSHPlayerController;
class UPanelSlot;

UCLASS()
class LSH_GAMEPROJECT_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	ALSHPlayerController* LSHPlayerController;
public:
	virtual void Init();
public:
	UWidgetBase(const FObjectInitializer& ObjectInitializer);
};

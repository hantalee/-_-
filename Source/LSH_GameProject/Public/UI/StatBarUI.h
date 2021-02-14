// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "StatBarUI.generated.h"

/**
 * 
 */
class UVerticalBox;
class UOverlay;
class UProgressBar;
class UTextBlock;

UCLASS()
class LSH_GAMEPROJECT_API UStatBarUI : public UWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UVerticalBox* Panel_VerticalBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UOverlay* Overlay_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UOverlay* Overlay_MP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* ProgressBar_HPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* ProgressBar_MPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TextBlock_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TextBlock_MP;
public:
	void AddEvent();
public:
	//DelgateFunc
	UFUNCTION()
		void DelFunc_CharacterHPChanged();
	UFUNCTION()
		void DelFunc_CharacterMPChanged();
public:
	virtual void Init() override;
public:
	UStatBarUI(const FObjectInitializer& ObjectInitializer);
};

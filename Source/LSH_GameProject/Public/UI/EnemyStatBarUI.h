// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "EnemyStatBarUI.generated.h"

/**
 * 
 */
class UVerticalBox;
class UOverlay;
class UProgressBar;
class UTextBlock;

class AEnemy;

UCLASS()
class LSH_GAMEPROJECT_API UEnemyStatBarUI : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UVerticalBox* Panel_VerticalBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UOverlay* Overlay_HP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UProgressBar* ProgressBar_HPBar;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* TextBlock_HP;
private:
	UPROPERTY(EditDefaultsOnly)
		AEnemy* Target;
public:
	void SetTarget(AEnemy* Enemy) { Target = Enemy; }
public:
	//DelgateFunc
	UFUNCTION()
		void DelFunc_EnemyHPChanged();
	UFUNCTION()
		void DelFunc_EnemyMPChanged();
public:
	void AddEvent();
public:
	virtual void Init() override;
public:
	UEnemyStatBarUI(const FObjectInitializer& ObjectInitializer);
};

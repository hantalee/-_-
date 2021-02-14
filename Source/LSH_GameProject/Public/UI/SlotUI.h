// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetBase.h"
#include "SlotUI.generated.h"

/**
 * 
 */
class UTextBlock;
class UImage;
class UGridPanel;
class UTexture2D;

UENUM(BlueprintType)
enum ESlotType
{
	Slot_None UMETA(DisplayName = "None"),
	Slot_Item UMETA(DisplayName = "Item"),
	Slot_Skill UMETA(DisplayName = "Skill"),
	Slot_Quick UMETA(DisplayName = "Quick"),
	Slot_Q_Item UMETA(DisplayName = "Q_Item"),
	Slot_Q_Skill UMETA(DisplayName = "Q_Skill"),
};

enum EItemType;

UCLASS()
class LSH_GAMEPROJECT_API USlotUI : public UWidgetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UGridPanel* Panel_Grid;	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UImage* Img_ItemIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Txt_ItemCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int SlotNum;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<EItemType> ItemType;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TEnumAsByte<ESlotType> SlotType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTexture2D* Texture_Icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture_DefaultIcon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ItemCount = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool IsUsed = false;
public:
	void SetSlotType(ESlotType Type);
	ESlotType const GetSlotType() { return SlotType; }

	void SetItemType(EItemType Type);
	EItemType const GetItemType() { return ItemType; }

	void SetTexture(UTexture2D* Texture);
	UTexture2D* const GetTexture();

	void SetTextByName(FName Name);
	void SetTextByString(FString String);

	void ChangeItemCount(int Count);
	void SetItemCount(int Count);
	int const GetItemCount();

	void SetSlotEmpty(UTexture2D* Texture);

	virtual void Init() override;
protected:
	// 마우스 드래그 시작
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	// 드랍 될때
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	// 버튼 눌릴때
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	USlotUI(const FObjectInitializer& ObjectInitializer);
};

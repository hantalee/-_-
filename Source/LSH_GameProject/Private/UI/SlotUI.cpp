// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SlotUI.h"

#include "Controller/LSHPlayerController.h"
#include "Object/Inventory.h"
#include "Object/SlotDrag.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetTree.h"


void USlotUI::SetSlotType(ESlotType Type)
{
	SlotType = Type;
}

void USlotUI::SetItemType(EItemType Type)
{
	ItemType = Type;
}

void USlotUI::SetTexture(UTexture2D* Texture)
{
	if (Texture == nullptr)
		return;

	Texture_Icon = Texture;
	Img_ItemIcon->SetBrushFromTexture(Texture);

}

UTexture2D* const USlotUI::GetTexture()
{
	if (Texture_Icon == nullptr)
		return nullptr;

	return Texture_Icon;
}

void USlotUI::SetTextByName(FName Name)
{
	if (Txt_ItemCount == nullptr)
		return;

	FText Text;
	Txt_ItemCount->SetText(Text.FromName(Name));
}

void USlotUI::SetTextByString(FString String)
{
	if (Txt_ItemCount == nullptr)
		return;

	FText Text;
	Txt_ItemCount->SetText(Text.FromString(String));
}

void USlotUI::ChangeItemCount(int Count)
{
	ItemCount += Count;

	if (ItemCount == 0)
		Txt_ItemCount->SetVisibility(ESlateVisibility::Hidden);
	else
		Txt_ItemCount->SetVisibility(ESlateVisibility::Visible);

	SetTextByString(FString::FromInt(ItemCount));
}

void USlotUI::SetItemCount(int Count)
{
	ItemCount = Count;

	if (ItemCount == 0)
		Txt_ItemCount->SetVisibility(ESlateVisibility::Hidden);
	else
		Txt_ItemCount->SetVisibility(ESlateVisibility::Visible);

	SetTextByString(FString::FromInt(ItemCount));
}

int const USlotUI::GetItemCount()
{
	return ItemCount;
}

void USlotUI::SetSlotEmpty(UTexture2D* Texture)
{
	SetTexture(Texture);
	SetItemType(Item_None);
	SetItemCount(0);
	IsUsed = false;
}

void USlotUI::Init()
{
	Panel_Grid = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	Img_ItemIcon = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass());
	Txt_ItemCount = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());

	WidgetTree->RootWidget = Panel_Grid;
	Panel_Grid->SetColumnFill(0, 1.0);
	Panel_Grid->SetRowFill(0, 1.0);

	Panel_Grid->AddChildToGrid(Img_ItemIcon,0,0);
	Panel_Grid->AddChildToGrid(Txt_ItemCount,0,0);

	UGridSlot* GridSlot_Img = Cast<UGridSlot>(Img_ItemIcon->Slot);
	GridSlot_Img->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
	GridSlot_Img->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);

	UGridSlot* GridSlot_Text = Cast<UGridSlot>(Txt_ItemCount->Slot);
	GridSlot_Text->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Right);
	GridSlot_Text->SetVerticalAlignment(EVerticalAlignment::VAlign_Bottom);

	Txt_ItemCount->SetColorAndOpacity(FLinearColor(0.0, 0.0, 0.0, 1.0));

	SetDesiredSizeInViewport(FVector2D(128, 128));
}


void USlotUI::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (OutOperation == nullptr)
	{
		USlotDrag* Oper = NewObject<USlotDrag>();
		OutOperation = Oper;
		Oper->FromNum = this->SlotNum;
		Oper->SlotType = this->SlotType;
		Oper->DefaultDragVisual = this; //Drag하는 동안 보여질 UI
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Drag Again"));
	}
}

bool USlotUI::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	USlotDrag* Oper = Cast<USlotDrag>(InOperation);

	if (Oper != nullptr)
	{
		LSHPlayerController->DraggingSwap(Oper->FromNum, Oper->SlotType, this->SlotNum, this->SlotType);
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

FReply USlotUI::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply Reply;
	Reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);


	//해당 슬롯이 미사용중이면
	if(!IsUsed)
		return Reply.NativeReply;

	//좌클릭
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		switch (SlotType)
		{
			case Slot_None: case Slot_Quick:
			{
				break;
			}
			case Slot_Item: case Slot_Q_Item:
			{
				//DetectDragIfPressed : OnDragDetected 함수 호출
				Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
				break;
			}
			case Slot_Skill: case Slot_Q_Skill:
			{
				break;
			}
			default:
				break;
		}
	}
	//우클릭
	else if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		switch (SlotType)
		{
			case Slot_None: case Slot_Quick:
			{
				return Reply.NativeReply;
				break;
			}
			case Slot_Item: case Slot_Q_Item:
			{
				LSHPlayerController->GetPlayerInventory()->UsedItem(SlotNum, ItemType);
				break;
			}
			case Slot_Skill: case Slot_Q_Skill:
			{
				break;
			}
			default:
				break;
		}
	}


	return Reply.NativeReply;
}

USlotUI::USlotUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

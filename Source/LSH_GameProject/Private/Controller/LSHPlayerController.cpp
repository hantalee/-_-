// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/LSHPlayerController.h"

#include "Object/PlayerCharacter.h"
#include "Object/Inventory.h"

#include "UI/MainGameUI.h"
#include "UI/InventoryUI.h"
#include "UI/SlotUI.h"

#include "Blueprint/UserWidget.h"
#include "UI/MainGameUI.h"

const FName ALSHPlayerController::MoveForwardAxis(TEXT("MoveForward"));
const FName ALSHPlayerController::MoveRightAxis(TEXT("MoveRight"));
const FName ALSHPlayerController::LookAroundAxis(TEXT("LookAround"));
const FName ALSHPlayerController::AttackAction(TEXT("Attack"));


FVector const ALSHPlayerController::GetMovementVector()
{
	const float InputX = InputComponent->GetAxisValue(MoveForwardAxis);
	const float InputY = InputComponent->GetAxisValue(MoveRightAxis);

	const FVector Forward = PlayerCharacter->GetActorForwardVector() * InputX;
	const FVector Right = PlayerCharacter->GetActorRightVector() * InputY;

	FVector Result = Forward + Right;
	return Result.GetClampedToSize(0.0f, 1.0f);
}

void ALSHPlayerController::OnAttackActionPressed()
{
	if (!IsValid(PlayerCharacter))
		return;

	if (PlayerCharacter->GetIsAttacking())
		return;

	PlayerCharacter->StartAttack();
}

void ALSHPlayerController::OnAttackActionRealed()
{
	if (!IsValid(PlayerCharacter))
		return;

	PlayerCharacter->StopAttack();
}

bool ALSHPlayerController::DraggingSwap(int From, ESlotType FromType, int To, ESlotType ToType)
{
	if (FromType == ESlotType::Slot_Item && (FromType == ToType))
		return SwapInventory(From, To);

	return false;
}

bool ALSHPlayerController::SwapInventory(int From, int To)
{
	if (From < 0 || To < 0)
		return false;

	//Inventory::ItemList
	Inventory->ItemList.Swap(From, To);
	Inventory->ItemObjectList.Swap(From, To);

	//InventoryUI::Slots
	MainGameUI->InventoryUI->SwapSlot(From, To);

	return true;
}

void ALSHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	Inventory = NewObject<UInventory>(this, InventoryClass);
	if (Inventory != nullptr)
	{
		Inventory->Init(PlayerCharacter);
	}

	if (MainGameUIClass != nullptr)
	{
		MainGameUI = CreateWidget<UMainGameUI>(this, MainGameUIClass);

		if (MainGameUI == nullptr)
			return;
		MainGameUI->LSHPlayerController = this;
		MainGameUI->Init();
		MainGameUI->AddToViewport();
	}
}

ALSHPlayerController::ALSHPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALSHPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(PlayerCharacter))
		return;

	PlayerCharacter->GetCharacterMovement()->AddInputVector(GetMovementVector());
}

void ALSHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveForwardAxis);
	InputComponent->BindAxis(MoveRightAxis);
	InputComponent->BindAxis(LookAroundAxis, this, &ALSHPlayerController::AddYawInput);

	InputComponent->BindAction(AttackAction, EInputEvent::IE_Pressed, this, &ALSHPlayerController::OnAttackActionPressed);
	//InputComponent->BindAction(AttackAction, EInputEvent::IE_Released, this, &ALSHPlayerController::OnAttackActionRealed);
}

void ALSHPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
}

void ALSHPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	PlayerCharacter = nullptr;
}

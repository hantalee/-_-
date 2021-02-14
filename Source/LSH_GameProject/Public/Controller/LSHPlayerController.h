// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LSHPlayerController.generated.h"

/**
 * 
 */
class APlayerCharacter;
class UInventory;
class UMainGameUI;

enum ESlotType;

UCLASS()
class LSH_GAMEPROJECT_API ALSHPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	static const FName MoveForwardAxis;
	static const FName MoveRightAxis;
	static const FName LookAroundAxis;
	static const FName AttackAction;
private:
	APlayerCharacter* PlayerCharacter;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UInventory> InventoryClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		UInventory* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UMainGameUI> MainGameUIClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		UMainGameUI* MainGameUI;
public:
	APlayerCharacter* GetPlayerInstance() { return PlayerCharacter; }

	FVector const GetMovementVector();
	UInventory* const GetPlayerInventory() { return Inventory; }

	void OnAttackActionPressed();
	void OnAttackActionRealed();

	bool DraggingSwap(int From, ESlotType FromType, int To, ESlotType ToType);
	bool SwapInventory(int From, int To);
protected:
	virtual void BeginPlay() override;
public:
	ALSHPlayerController();
	virtual void Tick(float DeltaTime) override;
public:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};

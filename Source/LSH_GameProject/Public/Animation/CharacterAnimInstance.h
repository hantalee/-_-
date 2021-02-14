// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 
 */
class ACharacterBase;

UCLASS()
class LSH_GAMEPROJECT_API UCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ACharacterBase* MyCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsFalling = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Direction = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float AttackSpeed = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bEquipWeapon = false;
private:
	UFUNCTION(BlueprintCallable)
		void AnimNotify_AttackStartCheck();
	UFUNCTION(BlueprintCallable)
		void AnimNotify_AttackStopCheck();
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;
protected:
	virtual void NativeBeginPlay() override;
};

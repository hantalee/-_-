// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
class UInputComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LSH_GAMEPROJECT_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;
public:
	virtual void KillCharacter() override;
protected:
	virtual void BeginPlay() override;
public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
};

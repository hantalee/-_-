// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/CharacterBase.h"
#include "Enemy.generated.h"

/**
 * 
 */
class UWidgetComponent;

UCLASS()
class LSH_GAMEPROJECT_API AEnemy : public ACharacterBase
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UWidgetComponent* WidgetComponent;
public:
	virtual void KillCharacter() override;
protected:
	virtual void BeginPlay() override;
public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
};

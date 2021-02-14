// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "Object/EquipItem.h"
#include "Weapon.generated.h"

class UBoxComponent;

class AEnemy;

UCLASS()
class LSH_GAMEPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
public:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
		FEquipmentItemDataRow Data;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AEnemy* AttackTarget;
protected:
	bool IsAttacking = false;
	FTimerHandle AttackTimer;
public:
	void StartAttack();
	void StopAttack();

	void Attack();
public:	
	AWeapon();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

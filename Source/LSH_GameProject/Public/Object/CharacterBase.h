// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterHPChange);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterMPChange);

USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FCharacterStat()
		:
		Id(NAME_None),
		MaxHP(0),
		CurrentHP(MaxHP),
		MaxMP(0),
		CurrentMP(MaxMP),
		MaxMoveSpeed(0),
		CurrentMoveSpeed(MaxMoveSpeed),
		AttackDamage(0)
	{};
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int MaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int CurrentMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentMoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AttackDamage;
};



class AWeapon;
class UEquipItem;
class UCharacterAnimInstance;
class UAnimMontage;

UCLASS()
class LSH_GAMEPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FCharacterStat CharacterStat;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FName CharacterRowName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UAnimMontage* AttackMontage;
public:
	//Delgate
	UPROPERTY(BlueprintAssignable)
		FCharacterHPChange ChangeHP;
	UPROPERTY(BlueprintAssignable)
		FCharacterMPChange ChangeMP;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool IsDead = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool IsAttacking = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AWeapon* Weapon = nullptr;
public:
	void StartAttack();
	void StopAttack();
	virtual void KillCharacter();

	UFUNCTION()
		void EquipItem(UEquipItem* InWeapon);
	UFUNCTION()
		void UnEquipWeapon();

	bool GetCharacterStatDataRow(FName InRowName, FCharacterStat* StatData);
public:
	ACharacterBase();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION()
		bool const GetIsAttacking() { return IsAttacking; }

	void SetId(FName Id);
	void SetHp(int ChangedHP);
	void SetMaxHp(int ChangedMaxHp);
	void SetMP(int ChangedMP);
	void SetMaxMp(int ChangedMaxMp);
	void SetSpeed(float ChangedSpeed);
	void SetMaxSpeed(int ChangedMaxSpeed);
	void SetAttackDamage(int ChangedAttackDamage);
public:
	FORCEINLINE AWeapon* GetWeapon() { return Weapon; }
	FORCEINLINE bool GetIsDead() { return IsDead; }

	FORCEINLINE FName const GetId() { return CharacterStat.Id; }
	FORCEINLINE int const GetHP() { return CharacterStat.CurrentHP; }
	FORCEINLINE int const GetMaxHP() { return CharacterStat.MaxHP; }
	FORCEINLINE int const GetMP() { return CharacterStat.CurrentMP; }
	FORCEINLINE int const GetMaxMP() { return CharacterStat.MaxMP; }
	FORCEINLINE int const GetSpeed() { return CharacterStat.CurrentMoveSpeed; }
	FORCEINLINE int const GetMaxSpeed() { return CharacterStat.MaxMoveSpeed; }
	FORCEINLINE int const GetAttackDamage() { return CharacterStat.AttackDamage; }
};

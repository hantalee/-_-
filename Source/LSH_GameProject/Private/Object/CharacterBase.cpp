// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/CharacterBase.h"

#include "GameInstance/LSHGameInstance.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"

#include "Object/Weapon.h"
#include "Object/EquipItem.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//Stat Init
	FCharacterStat TempStat;
	if (GetCharacterStatDataRow(CharacterRowName, &TempStat))
	{
		//Id
		SetId(TempStat.Id);
		//Hp
		SetMaxHp(TempStat.MaxHP); SetHp(CharacterStat.MaxHP);
		//Mp
		SetMaxMp(TempStat.MaxMP); SetMP(CharacterStat.MaxMP);
		//Speed
		SetMaxSpeed(TempStat.MaxMoveSpeed); SetSpeed(CharacterStat.MaxMoveSpeed);
		//AttackDamage
		SetAttackDamage(TempStat.AttackDamage);
	}

}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::StartAttack()
{
	if (IsValid(Weapon))
	{
		IsAttacking = true;
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
	}
}

void ACharacterBase::StopAttack()
{
	if (IsValid(Weapon))
	{
		IsAttacking = false;
		GetMesh()->GetAnimInstance()->Montage_Stop(AttackMontage->BlendOut.GetBlendTime(), AttackMontage);
	}
}

void ACharacterBase::KillCharacter()
{
	CharacterStat.CurrentHP = 0;
	IsDead = true;

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetController()->SetIgnoreLookInput(true);
}

void ACharacterBase::EquipItem(UEquipItem* InWeapon)
{
	if (!InWeapon)
		return;

	if (Weapon != nullptr)
		UnEquipWeapon();


	USkeletalMeshComponent* MyMesh = GetMesh();

	FEquipmentItemDataRow Row = InWeapon->GetEquipmentItemDataRow();
	ULSHGameInstance* Game = GetWorld()->GetGameInstance<ULSHGameInstance>();

	FActorSpawnParameters Params;
	Params.Owner = this;	

	Weapon = Game->SpawnEquipmentItem(Row, this->GetTransform(), Params);
	
	UPrimitiveComponent* WeaponRoot = Cast<UPrimitiveComponent>(Weapon->GetRootComponent());
	WeaponRoot->SetSimulatePhysics(false);
	WeaponRoot->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Weapon->AttachToComponent(MyMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Row.SocketName);

	InWeapon->IsUsed = true;
}

void ACharacterBase::UnEquipWeapon()
{
	Weapon->SetOwner(nullptr);
}

bool ACharacterBase::GetCharacterStatDataRow(FName InRowName, FCharacterStat* StatData)
{
	ULSHGameInstance* GameInst = GetWorld()->GetGameInstance<ULSHGameInstance>();
	ensure(GameInst);
	if (!GameInst)
		return false;

	UDataTable* StatTable = GameInst->GetCharacterStatDataTable();

	ensure(StatTable);
	if (!IsValid(StatTable))
		return false;

	FString Context;
	FCharacterStat* Row = StatTable->FindRow<FCharacterStat>(InRowName, Context);
	if (Row == nullptr)
		return false;

	*StatData = *Row;
	return true;
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACharacterBase::SetId(FName Id)
{
	CharacterStat.Id = Id;
}

void ACharacterBase::SetHp(int ChangedHP)
{
	if (CharacterStat.Id != NAME_None)
	{
		CharacterStat.CurrentHP += ChangedHP;
		if (CharacterStat.MaxHP < CharacterStat.CurrentHP)
			CharacterStat.CurrentHP = CharacterStat.MaxHP;
	}

	if (ChangeHP.IsBound())
		ChangeHP.Broadcast();
}

void ACharacterBase::SetMaxHp(int ChangedMaxHp)
{
	if (CharacterStat.Id != NAME_None)
		CharacterStat.MaxHP = ChangedMaxHp;
}

void ACharacterBase::SetMP(int ChangedMP)
{
	if (CharacterStat.Id != NAME_None)
	{
		CharacterStat.CurrentMP += ChangedMP;
		if (CharacterStat.MaxMP < CharacterStat.CurrentMP)
			CharacterStat.CurrentMP = CharacterStat.MaxMP;
	}

	if (ChangeMP.IsBound())
		ChangeMP.Broadcast();
}

void ACharacterBase::SetMaxMp(int ChangedMaxMp)
{
	if (CharacterStat.Id != NAME_None)
		CharacterStat.MaxMP = ChangedMaxMp;
}

void ACharacterBase::SetSpeed(float ChangedSpeed)
{
	if (CharacterStat.Id != NAME_None)
		CharacterStat.CurrentMoveSpeed = ChangedSpeed;
}

void ACharacterBase::SetMaxSpeed(int ChangedMaxSpeed)
{
	if (CharacterStat.Id != NAME_None)
		CharacterStat.MaxMoveSpeed = ChangedMaxSpeed;
}

void ACharacterBase::SetAttackDamage(int ChangedAttackDamage)
{
	if (CharacterStat.Id != NAME_None)
		CharacterStat.AttackDamage = ChangedAttackDamage;
}


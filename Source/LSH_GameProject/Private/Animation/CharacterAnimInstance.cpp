// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/CharacterAnimInstance.h"

#include "Object/PlayerCharacter.h"
#include "Object/Weapon.h"

#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::AnimNotify_AttackStartCheck()
{
	AWeapon* Weapon = MyCharacter->GetWeapon();
	if (IsValid(Weapon))
		Weapon->StartAttack();
}

void UCharacterAnimInstance::AnimNotify_AttackStopCheck()
{
	AWeapon* Weapon = MyCharacter->GetWeapon();
	if (IsValid(Weapon))
		Weapon->StopAttack();

	MyCharacter->StopAttack();
}

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!IsValid(MyCharacter))
		return;

	bIsFalling = MyCharacter->GetCharacterMovement()->IsFalling();
	Speed = MyCharacter->GetVelocity().Size();
	Direction = CalculateDirection(MyCharacter->GetVelocity(), MyCharacter->GetActorRotation());
	bAttacking = MyCharacter->GetIsAttacking();
}

void UCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	MyCharacter = Cast<ACharacterBase>(TryGetPawnOwner());
	check(MyCharacter);
}

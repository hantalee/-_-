// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Weapon.h"

#include "Object/Enemy.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "TimerManager.h"

void AWeapon::StartAttack()
{
	IsAttacking = true;
	BoxComponent->Activate();
}

void AWeapon::StopAttack()
{
	IsAttacking = false;
	BoxComponent->Deactivate();
}

void AWeapon::Attack()
{
	if (!IsValid(AttackTarget))
		return;

	float DamageAmout = (float)Data.AttackPower;
	FDamageEvent DamageEvent;
	AttackTarget->TakeDamage(DamageAmout, DamageEvent, GetInstigatorController(), this);
}

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	RootComponent = Mesh;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetGenerateOverlapEvents(IsAttacking);
	BoxComponent->SetCollisionProfileName(TEXT("Weapon"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsAttacking == false)
		return;

	if (OtherActor == GetOwner())
		return;

	AttackTarget = Cast<AEnemy>(OtherActor);
	if(IsValid(AttackTarget))
		Attack();
}


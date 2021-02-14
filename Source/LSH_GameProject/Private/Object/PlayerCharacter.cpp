// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/PlayerCharacter.h"


void APlayerCharacter::KillCharacter()
{
	ACharacterBase::KillCharacter();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Player"));
}

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (DamageAmount >= CharacterStat.CurrentHP)
	{
		KillCharacter();
	}
	else
	{
		SetHp(-DamageAmount);
	}

	// 최종적으로 이 액터에 적용된 대미지 반환 
	return DamageAmount;
}
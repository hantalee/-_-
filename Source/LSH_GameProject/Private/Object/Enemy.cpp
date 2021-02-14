// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Enemy.h"

#include "Blueprint/UserWidget.h"
#include "UI/EnemyStatBarUI.h"
#include "Components/WidgetComponent.h"


void AEnemy::KillCharacter()
{
	ACharacterBase::KillCharacter();

	WidgetComponent->SetVisibility(false);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* UserWidget = WidgetComponent->GetUserWidgetObject();
	UEnemyStatBarUI* StatBar = Cast<UEnemyStatBarUI>(UserWidget);
	StatBar->SetTarget(this);
	StatBar->Init();
}

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatBar"));
	WidgetComponent->SetupAttachment(RootComponent);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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
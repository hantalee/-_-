// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/CollisionItem.h"

#include "Object/PlayerCharacter.h"
#include "Controller/LSHPlayerController.h"
#include "Object/Inventory.h"
#include "Object/Item.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

ACollisionItem::ACollisionItem()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->InitBoxExtent(FVector::OneVector * 75.0f);
	BoxTrigger->SetCollisionProfileName(TEXT("Trigger"));
	BoxTrigger->SetGenerateOverlapEvents(true);
	RootComponent = BoxTrigger;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(BoxTrigger);
}

void ACollisionItem::BeginPlay()
{
	Super::BeginPlay();
}

void ACollisionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACollisionItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Owner != nullptr)
		Owner = nullptr;

	Owner = Cast<APlayerCharacter>(OtherActor);
	if (Owner == nullptr)
		return;

	ALSHPlayerController* Controller = Cast<ALSHPlayerController>(Owner->GetController());
	UInventory* Inventory = Controller->GetPlayerInventory();

	bool IsSuccess = Inventory->AddItem(ItemRowName, Count);
	if (IsSuccess)
		Destroy();
}


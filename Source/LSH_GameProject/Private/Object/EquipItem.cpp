// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/EquipItem.h"

#include "Object/CharacterBase.h"

UEquipItem::UEquipItem()
{
}

bool UEquipItem::Use(ACharacterBase* Target)
{
	UItem::Use(Target);

	return false;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/Item.h"

#include "Object/CharacterBase.h"

UItem::UItem()
{
}

bool UItem::Use(ACharacterBase* Target)
{
	return false;
}

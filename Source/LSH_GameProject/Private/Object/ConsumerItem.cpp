// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/ConsumerItem.h"

#include "Object/CharacterBase.h"

UConsumerItem::UConsumerItem()
{
}

bool UConsumerItem::Use(ACharacterBase* Target)
{
	UItem::Use(Target);

	FConsumerItemDataRow Data = GetConsumerItemDataRow();
	switch (Data.Type)
	{
	case Consum_None:
	{
		break;
	}
	case Consum_HP:
	{

		Target->SetHp(Data.Amount);
		return true;
		break;
	}
	case Consum_MP:
	{
		Target->SetMP(Data.Amount);
		return true;
		break;
	}
	default:
		break;
	}

	return false;
}

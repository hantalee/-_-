// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollisionItem.generated.h"

class APlayerCharacter;
class UBoxComponent;

UCLASS()
class LSH_GAMEPROJECT_API ACollisionItem : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* BoxTrigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMesh;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName ItemRowName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Count = 1;
private:
	APlayerCharacter* Owner;
public:	
	ACollisionItem();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};

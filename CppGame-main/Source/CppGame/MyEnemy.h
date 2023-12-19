// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.h"
#include "MyEnemy.generated.h"

UCLASS()
class CPPGAME_API AMyEnemy : public ACreature
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AMyEnemy();

protected:
	virtual void BeginPlay() override;
public:
	virtual void OnHit() override;
};

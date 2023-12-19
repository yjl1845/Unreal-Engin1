// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "MyPlayer.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API AMyPlayer : public ACreature
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
public:
	AMyPlayer();
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	void KeyUpDown(float value);
	void KeyLeftRight(float value);
	void LookLeftRight(float value);
	void LookUpDown(float value);
public:
	virtual void OnHit() override;
};

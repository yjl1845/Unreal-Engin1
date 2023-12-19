// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.generated.h"

UCLASS()
class CPPGAME_API ACreature : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere)
	bool IsAttacking = false;
	UPROPERTY(VisibleAnywhere)
	bool OnDeath = false;
	UPROPERTY(VisibleAnywhere)
	class UMyActorComponent* MyActorComponent;
	UPROPERTY(VisibleAnywhere)
	class UCratureAnim* CreatureAnimInstance;
	UPROPERTY(VisibleAnywhere)
	class UWidgetComponent* HpBar;
public:
	bool GetDeath() { return OnDeath; }

public:
	// Sets default values for this character's properties
	ACreature();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
public:
	virtual void Attack();
	virtual void OnHit();
	void CheckDeath();
	UFUNCTION()
	virtual void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
public:
	int GetHP();


};

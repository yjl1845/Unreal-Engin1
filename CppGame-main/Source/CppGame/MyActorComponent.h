// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpChanged);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPGAME_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = Info, Meta = (AllowPrivateAccess = true))
	int32 Level;
	UPROPERTY(EditAnywhere, Category = Info, Meta = (AllowPrivateAccess = true))
	int32 MaxHp;
	UPROPERTY(EditAnywhere, Category = Info, Meta = (AllowPrivateAccess = true))
	int32 Hp;
public:
	FOnHpChanged OnHpChanged;

public:	
	// Sets default values for this component's properties
	UMyActorComponent();

protected:
	virtual void InitializeComponent() override; // BeginPlay전에 호출
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	void SetLevel(int32 _Level);
	void OnDamaged(float DamageAmount);
	void SetHp(int32 _Hp);
	float GetHpRatio();
public:
	int32 GetLevel() { return Level; }
	int32 GetHp() { return Hp; }
		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindHp(class UMyActorComponent* ActorComp);
	void UpdateHp();
private:
	UPROPERTY()
	class UMyActorComponent* MyActorComp;
	UPROPERTY()
	class UProgressBar* PB_HpBar;
	
};

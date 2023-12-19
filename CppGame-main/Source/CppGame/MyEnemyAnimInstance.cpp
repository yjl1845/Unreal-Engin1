// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemyAnimInstance.h"

UMyEnemyAnimInstance::UMyEnemyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("/Script/Engine.AnimMontage'/Game/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage'"));
	if (AnimMontage.Succeeded())
	{
		AttackMontage = AnimMontage.Object;
	}
}



// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	ConstructorHelpers::FClassFinder<AMyCharacter> BP_Character(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_Player.BP_Player_C'"));
	if (BP_Character.Succeeded())
	{
		DefaultPawnClass = BP_Character.Class;
	}
	
}

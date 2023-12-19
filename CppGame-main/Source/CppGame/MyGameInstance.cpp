// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> Data(TEXT("/Script/Engine.DataTable'/Game/Data/DT_ChracterInfo.DT_ChracterInfo'"));
	
	if (Data.Succeeded())
	{
		CharacterDataTable = Data.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("Character Data : %d"), GetCharacterData(1)->MaxHp);
}

FMyCharacterData* UMyGameInstance::GetCharacterData(int32 Level)
{
	FName RowName = FName(*FString::Printf(TEXT("Lv%d"), Level));

	return CharacterDataTable->FindRow<FMyCharacterData>(RowName, TEXT(""));
}

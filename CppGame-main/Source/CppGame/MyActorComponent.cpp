// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "MyGameInstance.h" // GameInstace 사용하기 위해
#include "Kismet/GameplayStatics.h" // UGameplayStatics  사용하기 위해

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true; // InitializeComponet 호출 허락
	Level = 1;

	// ...
}


void UMyActorComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetLevel(Level);
}

// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UMyActorComponent::SetLevel(int32 _Level)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto CharacterData = MyGameInstance->GetCharacterData(_Level);	 
		if (CharacterData)
		{
			Level = CharacterData->Level;
			MaxHp = CharacterData->MaxHp;
			Hp = MaxHp;
		}
	}
}

void UMyActorComponent::OnDamaged(float DamageAmount)
{

	int32 NewHP = Hp - DamageAmount;
	SetHp(NewHP);
}

void UMyActorComponent::SetHp(int32 _Hp)
{
	Hp = _Hp;
	if (Hp < 0)
	{
		Hp = 0;
		//Todo
	}

	OnHpChanged.Broadcast();
}

float UMyActorComponent::GetHpRatio()
{
	if (MaxHp == 0 || Hp == 0)
	{
		return 0.f;
	}

	return (float)Hp / (float)MaxHp;
}



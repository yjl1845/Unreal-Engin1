// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"
#include "CratureAnim.h"
#include "MyActorComponent.h"
#include "Components/WidgetComponent.h"
#include "MyUserWidget.h"
#include "Components/CapsuleComponent.h"


ACreature::ACreature()
{
	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));

	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
	static ConstructorHelpers::FClassFinder<UMyUserWidget> MyUserWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_HpBar.WBP_HpBar_C'"));

	if (MyUserWidget.Succeeded())
	{
		HpBar->SetWidgetClass(MyUserWidget.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 30.f));
		HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();

	CreatureAnimInstance = Cast<UCratureAnim>(GetMesh()->GetAnimInstance());
	
	if (CreatureAnimInstance)
	{
		CreatureAnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackMontageEnded);
		CreatureAnimInstance->OnAttackHit.AddUObject(this, &ACreature::OnHit);
	}

	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(MyActorComponent);
	}

	MyActorComponent->OnHpChanged.AddUObject(this, &ACreature::CheckDeath);

}

float ACreature::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	MyActorComponent->OnDamaged(Damage);
	return Damage;
}

void ACreature::Attack()
{
	if (IsAttacking)
	{
		return;
	}

	if (IsValid(CreatureAnimInstance))
	{
		CreatureAnimInstance->PlayAttackMontage();
		IsAttacking = true;
	}
}

void ACreature::OnHit()
{
	//UE_LOG(LogTemp, Warning, TEXT("On Hit"));
}

void ACreature::CheckDeath()
{
	if (MyActorComponent->GetHp() <= 0)
	{
		OnDeath = true;
	};
}

void ACreature::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

int ACreature::GetHP()
{
	return MyActorComponent->GetHp();
}

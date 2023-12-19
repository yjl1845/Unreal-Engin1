// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEnemy.h"
#include "Components/CapsuleComponent.h"
#include "MyAIController.h"
#include "MyEnemyAnimInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyEnemy::AMyEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));



	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_MyEnemy.ABP_MyEnemy_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimInstance.Class);
	}

	AIControllerClass = AMyAIController::StaticClass();

}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AMyEnemy::OnHit()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	bool Result = GetWorld()->SweepSingleByChannel
	(OUT HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * AttackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(AttackRadius),
		Params);

	FVector Center = GetActorLocation();
	FVector Forward = GetActorLocation() + GetActorForwardVector() * AttackRange;

	float HalfHeight = AttackRange * 0.5f + AttackRange; 
	FQuat Rotation = FRotationMatrix::MakeFromZ(Forward).ToQuat();
	FColor DrawColor;

	if (Result && HitResult.GetActor())
	{
		DrawColor = FColor::Green;

		AActor* HitActor = HitResult.GetActor();
		UGameplayStatics::ApplyDamage(HitActor, 10.f, GetController(), nullptr, NULL);
	}
	else
	{
		DrawColor = FColor::Red;
	}

	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);
	
}


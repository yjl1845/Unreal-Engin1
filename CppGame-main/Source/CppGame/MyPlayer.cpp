// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "MyAnimInstance.h"
#include "Arrow.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

AMyPlayer::AMyPlayer()
{	 // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 400.f;
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));
	SpringArm->SocketOffset = FVector(0.f, 120.f, 75.f); //Ãß°¡
	SpringArm->bUsePawnControlRotation = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));

	if (SkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SkeletalMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.0f), FRotator(0.f, -90.f, 0.f));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_MyCharacter.ABP_MyCharacter_C'"));
	if (AnimInstance.Succeeded())
	{
		GetMesh()->SetAnimClass(AnimInstance.Class);
	}
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPlayer::KeyUpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPlayer::KeyLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeftRight"), this, &AMyPlayer::LookLeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUpDown"), this, &AMyPlayer::LookUpDown);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyPlayer::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AMyPlayer::Attack);

}

void AMyPlayer::KeyUpDown(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMyPlayer::KeyLeftRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AMyPlayer::LookLeftRight(float value)
{
	AddControllerYawInput(value);
}

void AMyPlayer::LookUpDown(float value)
{
	AddControllerPitchInput(value);
}


void AMyPlayer::OnHit()
{
	float AttackRange = 10000.f;

	FHitResult HitResult;

	APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	FVector AimLocation = CamManager->GetCameraLocation();
	FVector TargetLocation = CamManager->GetActorForwardVector() * AttackRange + AimLocation;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);

	bool Result = GetWorld()->LineTraceSingleByChannel
	(
		OUT HitResult,
		AimLocation,
		TargetLocation,
		ECollisionChannel::ECC_GameTraceChannel3,
		params
	);

	if (Result)
	{
		TargetLocation = HitResult.ImpactPoint;
		DrawDebugLine(GetWorld(), AimLocation, TargetLocation, FColor::Green, true);
	}
	else
	{
		DrawDebugLine(GetWorld(), AimLocation, TargetLocation, FColor::Red, true);
	}
	
	FTransform SocketTransform = GetMesh()->GetSocketTransform(FName("BowEmitterSocket"));
	FVector ShootPoint = SocketTransform.GetLocation();

	FVector DeltaVector = TargetLocation - ShootPoint;
	FRotator ShootRotation = FRotationMatrix::MakeFromX(DeltaVector).Rotator();
	FActorSpawnParameters ArrowParams;
	ArrowParams.Owner = this;
	ArrowParams.Instigator = this;

	//
	auto MyArrow = GetWorld()->SpawnActor<AArrow>(ShootPoint, ShootRotation, ArrowParams);



}

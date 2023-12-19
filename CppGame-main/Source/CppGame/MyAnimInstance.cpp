// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/KismetMathLibrary.h>

UMyAnimInstance::UMyAnimInstance()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("/Script/Engine.AnimMontage'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Animations/Primary_Fire_Med_Montage.Primary_Fire_Med_Montage'"));
	if (AnimMontage.Succeeded())
	{
		AttackMontage = AnimMontage.Object;
	}
}


void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Creature))
	{

		AimRotation = Creature->GetBaseAimRotation();
		FRotator BaseAimRotation = UKismetMathLibrary::MakeRotFromX(Velocity);
		
		FRotator DeltaRotation = BaseAimRotation - AimRotation;
		DeltaRotation.Normalize();

		YawOffset = DeltaRotation.Yaw;

			  
		if (ShouldMove || IsFalling)
		{
			RotateYaw = FMath::FInterpTo(RotateYaw, 0.f, DeltaSeconds, 20.0f);
			MovingRotation = Creature->GetActorRotation();
			FinalRotation = MovingRotation;
		}
		else
		{
			FinalRotation = MovingRotation;
			MovingRotation = Creature->GetActorRotation();
			FRotator Delta = MovingRotation - FinalRotation;
			Delta.Normalize();
			RotateYaw -= Delta.Yaw;

			float TurnValue = GetCurveValue("Turn");
			if (TurnValue > 0.f)
			{
				FinalDistanceCurve = DistanceCurve;
				DistanceCurve = GetCurveValue("DistanceCurve");
				float DeltaDistanceCurve = DistanceCurve - FinalDistanceCurve;
				if (RotateYaw > 0.f)
				{
					RotateYaw -= DeltaDistanceCurve;
				}
				else
				{
					RotateYaw += DeltaDistanceCurve;
				}

				float AbsRotateYawOffset = FMath::Abs(RotateYaw);
			
				if (AbsRotateYawOffset > 0.f)
				{
					float YawExcess = AbsRotateYawOffset - 90.f;
					
					if (RotateYaw > 0.f)
					{
						
						RotateYaw -= YawExcess;
					}
					else
					{
						RotateYaw += YawExcess;
					}

				}
			}

		
		}

	}
}

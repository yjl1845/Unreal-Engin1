// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CratureAnim.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UMyAnimInstance : public UCratureAnim
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RotateYaw; 
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float YawOffset;
	UPROPERTY(Category = Animation, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator AimRotation;
	
private:
	UPROPERTY(VisibleAnywhere)
	FRotator MovingRotation;
	UPROPERTY(VisibleAnywhere)
	FRotator FinalRotation;
	UPROPERTY(VisibleAnywhere)
	float FinalDistanceCurve;
	UPROPERTY(VisibleAnywhere)
	float DistanceCurve;
public:
	UMyAnimInstance();
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
};

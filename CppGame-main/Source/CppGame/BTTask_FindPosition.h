// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPosition.generated.h"

/**
 * 
 */
UCLASS()
class CPPGAME_API UBTTask_FindPosition : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_FindPosition();
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};

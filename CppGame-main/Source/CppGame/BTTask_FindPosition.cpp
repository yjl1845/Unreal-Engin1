// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPosition.h"
#include "AIController.h"
#include "NavigationSystem.h"	  
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindPosition::UBTTask_FindPosition()
{
	NodeName = TEXT("FindRandomPosition");
}

EBTNodeResult::Type UBTTask_FindPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn != nullptr)
	{
		auto NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
		if (NavSystem != nullptr)
		{
			FNavLocation RandomLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(CurrentPawn->GetActorLocation(), 500.f, RandomLocation))
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName("Destination"), RandomLocation.Location);
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}

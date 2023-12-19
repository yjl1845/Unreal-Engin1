// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"
#include "AIController.h"
#include "MyPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");
	Interval = 1.f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn != nullptr)
	{
		UWorld* World = CurrentPawn->GetWorld();
		
		if (World != nullptr)
		{
			FVector Center = CurrentPawn->GetActorLocation();
			float SearchDistance = 500.f;
			TArray<FOverlapResult> OverlapResults;
			FCollisionQueryParams QueryParams(NAME_Name, false, CurrentPawn);

			bool Result = World->OverlapMultiByChannel
			(
				OverlapResults,
				Center,
				FQuat::Identity,
				ECollisionChannel::ECC_EngineTraceChannel2,
				FCollisionShape::MakeSphere(SearchDistance),
				QueryParams
			);

			if (Result)
			{
				for (auto& OverlapResult : OverlapResults)
				{
					AMyPlayer* MyPlayer = Cast<AMyPlayer>(OverlapResult.GetActor());
					if (MyPlayer)
					{
						DrawDebugSphere(World, Center, SearchDistance, 10, FColor::Green, false, 0.5f);
						OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), MyPlayer);
						return;
					}
				}

				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);
				DrawDebugSphere(World, Center, SearchDistance, 10, FColor::Red, false, 0.5f);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target"), nullptr);
				DrawDebugSphere(World, Center, SearchDistance, 10, FColor::Red, false, 0.5f);
			}
			
		}

	}

}

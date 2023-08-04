// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_Heal.h"

#include "AIController.h"
#include "SAttributeComponent.h"

EBTNodeResult::Type USBTTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if(MyController)
	{
		APawn* MyPawn = MyController->GetPawn();

		if(MyPawn)
		{
			USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(MyPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

			if(AttributeComp)
			{
				AttributeComp->ApplyHealthChange(MyPawn, AttributeComp->GetMaxHealth());

				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"

#include "AIController.h"
#include "SAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(BlackboardComp)
	{
		AAIController* MyController = OwnerComp.GetAIOwner();

		if(MyController)
		{
			APawn* AIPawn = MyController->GetPawn();

			if(AIPawn)
			{
				USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(AIPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

				bool bIsLowHealth = false;

				if((AttributeComp->GetHealth() * 100 / AttributeComp->GetMaxHealth()) < 40)
				{
					bIsLowHealth = true;
				}

				BlackboardComp->SetValueAsBool("IsLowHealth", bIsLowHealth);
			}
		}
	}
}

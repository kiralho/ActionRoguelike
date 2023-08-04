// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotion.h"

#include "SAttributeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASHealthPotion::ASHealthPotion()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComp;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereComp);

	Healing = 20.0f;
	EnableTime = 10;
}

void ASHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		if(!AttributeComp->IsMaxHealth())
		{
			SetActorEnableCollision(false);
			StaticMesh->ToggleVisibility(false);
			AttributeComp->ApplyHealthChange(this, Healing);

			FTimerHandle EnablePotionTimer;
			GetWorldTimerManager().SetTimer(EnablePotionTimer, this, &ASHealthPotion::EnablePotion_TimeElapsed, EnableTime);
		}
	}
}

void ASHealthPotion::EnablePotion_TimeElapsed()
{
	SetActorEnableCollision(true);
	StaticMesh->ToggleVisibility(true);
}


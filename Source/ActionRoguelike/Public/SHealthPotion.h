// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "SHealthPotion.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API ASHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASHealthPotion();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	
protected:

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	float Healing;

	float EnableTime;

	void EnablePotion_TimeElapsed();

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASProjectile.h"
#include "ASBlackholeProjectile.generated.h"

/**
 * 
 */

class URadialForceComponent;

UCLASS()
class ACTIONROGUELIKE_API AASBlackholeProjectile : public AASProjectile
{
	GENERATED_BODY()

public:
	
	AASBlackholeProjectile();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialForceComp;
	
};

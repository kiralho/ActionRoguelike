// Fill out your copyright notice in the Description page of Project Settings.


#include "ASBlackholeProjectile.h"

#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

AASBlackholeProjectile::AASBlackholeProjectile()
{
	MovementComp->InitialSpeed = 500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->ForceStrength = -500000.0f;
	RadialForceComp->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "ASTeleportProjectile.h"

#include "MovieSceneTracksPropertyTypes.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AASTeleportProjectile::AASTeleportProjectile()
{
	MovementComp->InitialSpeed = 6000.0f;
}

// Called when the game starts or when spawned
void AASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentHit.AddDynamic(this, &AASTeleportProjectile::OnCompHit);
	GetWorldTimerManager().SetTimer(TimerHandle_ExplodeProjectile, this, &AASTeleportProjectile::ExplodeProjectile, 0.2f);
}

void AASTeleportProjectile::ExplodeProjectile()
{
	GetWorldTimerManager().ClearTimer((TimerHandle_ExplodeProjectile));
	MovementComp->StopMovementImmediately();
	EffectComp->DeactivateSystem();
	SetActorEnableCollision(false);
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportCharacter, this, &AASTeleportProjectile::TeleportCharacter, 0.2f);
}

void AASTeleportProjectile::TeleportCharacter()
{
	AActor* InstigatorActor = Cast<AActor>(GetInstigator());
	if(InstigatorActor)
	{
		FVector EndLocation = GetActorLocation();

		bool bTeleportSuccess = InstigatorActor->TeleportTo(EndLocation, InstigatorActor->GetActorRotation());

		if(!bTeleportSuccess)
		{
			EndLocation.Z = EndLocation.Z + 100.0f;
			InstigatorActor->TeleportTo(EndLocation, InstigatorActor->GetActorRotation());
		}
	}

	Destroy();
}

void AASTeleportProjectile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor != GetInstigator())
	{
		ExplodeProjectile();
	}
}
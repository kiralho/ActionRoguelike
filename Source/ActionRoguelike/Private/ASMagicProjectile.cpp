// Fill out your copyright notice in the Description page of Project Settings.


#include "ASMagicProjectile.h"

#include "SAttributeComponent.h"
#include "SGamePlayFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AASMagicProjectile::AASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Damage = 20.0f;
}

void AASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &AASMagicProjectile::OnCompHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AASMagicProjectile::OnActorOverlap);
}

void AASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* MyActor = GetInstigator();
	if(OtherActor && OtherActor != GetInstigator() && !OtherActor->IsA(AASMagicProjectile::StaticClass()))
	{
		// USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		//
		// if(AttributeComp)
		// {
		// 	AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
		//
		// 	Destroy();
		// }

		if(USGamePlayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, SweepResult))
		{
			Destroy();
		}
	}
}

void AASMagicProjectile::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor && OtherActor != GetInstigator() && !OtherActor->IsA(AASMagicProjectile::StaticClass()))
	{
		FVector ActorLocation = GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		FTransform ImpactTransform = FTransform(ActorRotation,ActorLocation);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, ImpactTransform);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBase, ActorLocation, ActorRotation);
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), ImpactCameraShake, ActorLocation, 5000, 1);
		Destroy();
	}
}




// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASProjectile.h"
#include "ASTeleportProjectile.generated.h"

/**
 * 
 */

class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AASTeleportProjectile : public AASProjectile
{
	GENERATED_BODY()

protected:

	FTimerHandle TimerHandle_ExplodeProjectile;
	
	FTimerHandle TimerHandle_TeleportCharacter;
	
public:

	AASTeleportProjectile();

protected:

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ExplodeParticleComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ExplodeProjectile();

	void TeleportCharacter();

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};

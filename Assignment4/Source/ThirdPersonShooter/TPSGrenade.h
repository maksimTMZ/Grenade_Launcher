// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TPSGrenade.generated.h"


class UHealthComponent;
UCLASS()
class THIRDPERSONSHOOTER_API ATPSGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATPSGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UHealthComponent* HealthComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHealthChanged(UHealthComponent* OwningHealthComp, 
								float Health, 
								float DeltaHealth, 
								const class UDamageType* DamageType, 
								class AController* InstigatedBy, 
								AActor* DamageCauser);

	UPROPERTY(ReplicatedUsing=OnRep_Exploded)
	bool bExploded;

	UFUNCTION()
	void OnRep_Exploded();

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float ExplosionImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UParticleSystem* ExplosionEffect;



	void DamageSelf();
	FTimerHandle SelfDamageTimer;






public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

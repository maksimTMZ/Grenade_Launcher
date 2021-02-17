// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGrenade.h"
#include "HealthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"





// Sets default values
ATPSGrenade::ATPSGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	HealthComp->OnHealthChanged.AddDynamic(this, &ATPSGrenade::OnHealthChanged);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetSimulatePhysics(true);

	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	RootComponent = MeshComp;

	ExplosionImpulse = 400;

	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ATPSGrenade::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(SelfDamageTimer, this, &ATPSGrenade::DamageSelf, 0.5f, true, 0);

}

void ATPSGrenade::OnHealthChanged(UHealthComponent * OwningHealthComp, 
									float Health,
									float DeltaHealth,
									const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	if (bExploded)
	{
		// Do nothing. Add destroy
		return;
	}

	if (Health <= 0.0f)
	{
		bExploded = true;
		OnRep_Exploded();

		// Apply radical damage
		TArray<AActor*> IgnoredActors;
		UGameplayStatics::ApplyRadialDamage(this, 100, GetActorLocation(), 200, nullptr, IgnoredActors, this, GetInstigatorController(), true);
		DrawDebugSphere(GetWorld(), GetActorLocation(), 200, 24, FColor::Blue, false, 5, 0, 1);
		Destroy();
	}

}

void ATPSGrenade::OnRep_Exploded()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
}

void ATPSGrenade::DamageSelf()
{
	UGameplayStatics::ApplyDamage(this, 20, GetInstigatorController(), this, nullptr);
}

void ATPSGrenade::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATPSGrenade, bExploded);
}




// Called every frame
void ATPSGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


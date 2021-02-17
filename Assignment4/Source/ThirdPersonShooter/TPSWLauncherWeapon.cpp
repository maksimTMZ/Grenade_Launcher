// Fill out your copyright notice in the Description page of Project Settings.
#include "TPSWLauncherWeapon.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

void ATPSWLauncherWeapon::Fire()
{
	AActor* myOwner = GetOwner();
	if (myOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		FVector EyeDirection = EyeLocation + (EyeRotation.Vector() * 10000);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector MuzzleLocation = MeshComp->GetSocketLocation(MuzzleSocketName);

		GetWorld()->SpawnActor<AActor>(LauncherClass, MuzzleLocation, EyeRotation, SpawnParams);

	}
}

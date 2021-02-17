// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "TPSWeapon.h"


#include "CoreMinimal.h"
#include "TPSWLauncherWeapon.generated.h"



/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API ATPSWLauncherWeapon : public ATPSWeapon
{
	GENERATED_BODY()


public:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Launcher")
	TSubclassOf<AActor>	LauncherClass;
	
};

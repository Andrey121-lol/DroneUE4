// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneBasePw.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enami_Base.generated.h"


/**
 * 
 */
UCLASS()
class DRON_API AEnami_Base : public ADroneBasePw
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:

	float SensingRange = 1500;

	void FindTarget();
	
};

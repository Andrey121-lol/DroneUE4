// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneBasePw.h"
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
	float SpeedRotation = 5000;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "var")
	AActor* Target ;
	TArray<AActor*> FoundActors;

	
	bool HaslineOfDight(FVector From ,FVector To,TArray<AActor*> ActorsToIgnore);
	void FindTarget();
	void UpdRotation(float DeltaSeconds);
	
};

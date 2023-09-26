// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxAmmo.h"

void ABoxAmmo::AddResourcesToPlayer(float Value)
{
	ValuesResurs=100;
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
	ADroneBasePw* Drone = Cast<ADroneBasePw>(PlayerPawn);
	if (Drone)
	{
		Drone->AddAmo(ValuesResurs);
		Drone->CanShoot=true;
	}


}


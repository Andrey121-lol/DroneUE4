// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxShield.h"

void ABoxShield::AddResourcesToPlayer(float Value)
{
	ValuesResurs=100;
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
	ADroneBasePw* Drone = Cast<ADroneBasePw>(PlayerPawn);
	if (Drone)
	{
		Drone->AddShield(ValuesResurs);
		Drone->CanShield=true;
	}


}


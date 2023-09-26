// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxMedic.h"

void ABoxMedic::AddResourcesToPlayer(float Value)
{
	ValuesResurs=20;
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
	ADroneBasePw* Drone = Cast<ADroneBasePw>(PlayerPawn);
	if (Drone)
	{
		Drone->AddHP(ValuesResurs);
	}


}

// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxWin.h"

void ABoxWin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 200.0f;       
	float DeltaRotation = DeltaTime * 50.0f;    
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);
}

void ABoxWin::AddResourcesToPlayer(float Value)
{
	Super::AddResourcesToPlayer(Value);
	ADroneBasePw* Drone = Cast<ADroneBasePw>(PlayerPawn);
	if (Drone)
	{
		Drone->Win();
	}

}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Enami_Base.h"

void AEnami_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnami_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
}

void AEnami_Base::FindTarget()
{
	float BastDist=SensingRange+1;
	float CurrentDist=0;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // Specify object types if needed.
	UClass* ActorClassFilter = nullptr; // Specify actor class filter if needed.
	TArray<AActor*> ActorsToIgnore; // Specify actors to ignore if needed.
	TArray<AActor*> OutActors;
	
	bool bOverlap = UKismetSystemLibrary::SphereOverlapActors(
	   this, // World context object.
	   GetActorLocation(), // Sphere position.
	   SensingRange, // Sphere radius.
	   ObjectTypes, // Object types to consider (can be empty).
	   ActorClassFilter, // Actor class filter (can be nullptr).
	   ActorsToIgnore, // Actors to ignore (can be empty).
	   OutActors // Array to store overlapping actors.
   );

	if (OutActors.Num() > 0)
	{
		AActor* FirstOverlappingActor = OutActors[0];

		// Вы можете использовать FirstOverlappingActor для выполнения дополнительных действий.
		// Например, вы можете проверить его класс, получить его координаты и так далее.
		for (int i = 0;i<OutActors.Num();i++)
		{
			FString ActorName = OutActors[i]->GetName();
			//UE_LOG(LogTemp, Warning, TEXT("Overlapping Actor's Name: %s"), *ActorName);
		}
		
	}
	
	
}



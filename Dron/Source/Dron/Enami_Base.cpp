// Fill out your copyright notice in the Description page of Project Settings.


#include "Enami_Base.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


void AEnami_Base::BeginPlay()
{
	Super::BeginPlay();
	IfDron =false;

	UClass* ClassToFind = AEnami_Base::StaticClass();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	
	
	
}

void AEnami_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
	UpdRotation(DeltaTime);
}

bool AEnami_Base::HaslineOfDight(FVector From, FVector To, TArray<AActor*> ActorsToIgnore)
{
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(ActorsToIgnore);

	// Выполняем лучевой трассировки от точки From к точке To.
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,     // Результат трассировки.
		From,          // Начальная точка.
		To,            // Конечная точка.
		ECC_Visibility, // Канал трассировки (может потребоваться настроить).
		CollisionParams // Параметры трассировки.
	);

	// Если луч попал в объект, bHit будет true, иначе - false.
	return !bHit;
}

void AEnami_Base::FindTarget()
{
	float BestDist=SensingRange+1;
	float CurrentDist=0;
	AActor* BestTarget = nullptr;
	AActor* CurrentTarget=nullptr;
	

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // Specify object types if needed.
	UClass* ActorClassFilter = nullptr; // Specify actor class filter if needed.
	TArray<AActor*> ActorsToIgnore; // Specify actors to ignore if needed.
	ActorsToIgnore.Add(this);
	for (int i =0;i<FoundActors.Num();i++)
	{
		ActorsToIgnore.Add(FoundActors[i]);

	}
	
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
		
		for (int i = 0;i<OutActors.Num();i++)
		{
			FString ActorName = OutActors[i]->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Overlapping Actor's Name: %s"), *ActorName);
			CurrentTarget = OutActors[i];
			CurrentDist = CurrentTarget->GetDistanceTo(this);
			if(CurrentDist<BestDist || !BestTarget)
			{
				TArray<AActor*> ActorsToIgnore2;
				ActorsToIgnore2.Add(this);
				ActorsToIgnore2.Add(CurrentTarget);
				
				bool result = HaslineOfDight(Head->GetRelativeLocation(),CurrentTarget->GetActorLocation(),ActorsToIgnore2);
				if(result)
				{
					BestTarget=CurrentTarget;
					BestDist=CurrentDist;
				}
			}
		}
		Target=BestTarget;
		
	}
	
	
}

void AEnami_Base::UpdRotation(float DeltaSeconds)
{
	if(Target)
	{
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(Mesh->GetRelativeLocation(), Target->GetActorLocation());
		FRotator ReinerpRot=UKismetMathLibrary::RInterpTo_Constant(Mesh->GetRelativeRotation(),NewRotation,DeltaSeconds,SpeedRotation);
		Head->SetWorldRotation(ReinerpRot);
	}
	
}



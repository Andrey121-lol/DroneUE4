// Fill out your copyright notice in the Description page of Project Settings.


#include "TurelBase.h"
#include "A_Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATurelBase::ATurelBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	BaseTurel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HeadTurel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
	GunTurel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	GunTurel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun2"));

	BaseTurel->SetupAttachment(Box);
	HeadTurel->SetupAttachment(BaseTurel);
	GunTurel1->SetupAttachment(HeadTurel);
	GunTurel2->SetupAttachment(HeadTurel);


}

// Called when the game starts or when spawned
void ATurelBase::BeginPlay()
{
	Super::BeginPlay();
	UClass* ClassToFind = ATurelBase::StaticClass();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

	
}

// Called every frame
void ATurelBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
	UpdRotation(DeltaTime);

}



bool ATurelBase::HaslineOfDight(FVector From, FVector To, TArray<AActor*> ActorsToIgnore)
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

void ATurelBase::FindTarget()
{
	float BestDist=SensingRange+1;
	float CurrentDist=0;
	AActor* BestTarget = nullptr;
	AActor* CurrentTarget=nullptr;
	

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // Specify object types if needed.
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
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
				
				bool result = HaslineOfDight(HeadTurel->GetComponentLocation(),CurrentTarget->GetActorLocation(),ActorsToIgnore2);
				if(result)
				{
					BestTarget=CurrentTarget;
					BestDist=CurrentDist;
				}
			}
		}
		
			Target = BestTarget;
		
		
		
	}
	
	
}

void ATurelBase::UpdRotation(float DeltaSeconds)
{
	
	if(Target)
	{
		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(HeadTurel->GetComponentLocation(), Target->GetActorLocation());
		FRotator ReinerpRot=UKismetMathLibrary::RInterpTo_Constant(HeadTurel->GetComponentRotation(),NewRotation,DeltaSeconds,SpeedRotation);
		HeadTurel->SetWorldRotation(ReinerpRot);
	}
	
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TurelBase.h"
#include "DroneBasePw.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

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
	// Убедимся, что PlayerPawn равен nullptr перед началом поиска.
	PlayerPawn = nullptr;
	
	UClass* ClassToFind = ADroneBasePw::StaticClass(); // Замените на класс игрока.

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);
	if (FoundActors.Num() > 0)
	{
		// Ваш код ищет только одного игрока, если найдено несколько, то выберется первый.
		PlayerPawn = FoundActors[0];
	}


	
}

// Called every frame
void ATurelBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsLive)
	{
		FindTarget();
		UpdRotation(DeltaTime);
		UpdFire();
	}

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
	float BestDist = SensingRange + 1;
	float CurrentDist = 0;
	AActor* BestTarget = nullptr;
	AActor* CurrentTarget = nullptr;

	TArray<AActor*> OutActors;

	// Изменим метод сферического поиска только на поиск всех актеров в указанном радиусе.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADroneBasePw::StaticClass(), OutActors);

	if (OutActors.Num() > 0)
	{
		for (AActor* Actor : OutActors)
		{
			CurrentTarget = Actor;
			CurrentDist = CurrentTarget->GetDistanceTo(this);

			if (CurrentDist <= SensingRange)
			{
				TArray<AActor*> ActorsToIgnore2;
				ActorsToIgnore2.Add(this);
				ActorsToIgnore2.Add(CurrentTarget);

				bool result = HaslineOfDight(HeadTurel->GetComponentLocation(), CurrentTarget->GetActorLocation(), ActorsToIgnore2);

				if (result)
				{
					if (CurrentDist < BestDist || !BestTarget)
					{
						BestTarget = CurrentTarget;
						BestDist = CurrentDist;
					}
				}
			}
		}
	}

	// Если не нашли игрока в радиусе, сбрасываем Target.
	Target = BestTarget;
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

void ATurelBase::DamageF(float Value)
{
	if(HP>0)
	{
		HP-=Value;
	}
	else if (HP<=0)
	{
		HP=0;
		Dead();
	}
}

void ATurelBase::Dead()
{
	IsLive=false;
	AttackFReleas();
	HeadTurel->DestroyComponent();
	GunTurel1->DestroyComponent();
	GunTurel2->DestroyComponent();
}

void ATurelBase::UpdFire()
{
	if (Target)
	{
		FVector UnitDirectionVector =GetUnitDirectionVector(HeadTurel->GetComponentLocation(),Target->GetActorLocation());
		FVector ForwardVectorHead=HeadTurel->GetForwardVector();
		DotProductValue = GetDotProductTo(UnitDirectionVector,ForwardVectorHead);
		if (DotProductValue<0.99 && Target)
		{
			AttackFPres(GunTurel1);
			AttackFPres(GunTurel2);
		}
	}
	else 
	{
		AttackFReleas();
	}
	
}

FVector ATurelBase::GetUnitDirectionVector(FVector StartVector, FVector EndVector)
{
	// Получаем направление от StartVector к EndVector
	FVector Direction = (EndVector - StartVector).GetSafeNormal();

	return Direction;
}

float ATurelBase::GetDotProductTo(FVector VectorA, FVector VectorB)
{
	// Вычислить dot product (скалярное произведение) между двумя векторами
	float DotProduct = FVector::DotProduct(VectorA, VectorB);

	return DotProduct;
}

void ATurelBase::Fire(class UStaticMeshComponent* Gun)
{
	AA_Projectile* SpawnP = GetWorld()->SpawnActor<AA_Projectile>(ProjectileClass,Gun->GetSocketTransform("Gun"));
}

void ATurelBase::AttackFPres(class UStaticMeshComponent* Gun)
{
	if (CanShoot)
	{
		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([this, Gun]() {
			Fire(Gun);
		});

		if (Gun == GunTurel1)
		{
			GetWorldTimerManager().SetTimer(MemberTimerHandle1, TimerCallback, 0.3f, true, 0.3f);
		}
		else if (Gun == GunTurel2)
		{
			GetWorldTimerManager().SetTimer(MemberTimerHandle2, TimerCallback, 0.3f, true, 0.3f);
		}
	}
}

void ATurelBase::AttackFReleas()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandle1);
	GetWorldTimerManager().ClearTimer(MemberTimerHandle2);
}

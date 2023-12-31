// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Projectile.h"
#include "DroneBasePw.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TurelBase.h"

using namespace std;
// Sets default values
AA_Projectile::AA_Projectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach the box component
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	// Create and attach the static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void AA_Projectile::BeginPlay()
{
	Super::BeginPlay();
	if (Box)
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &AA_Projectile::OnOverlapBegin);
	}
	GetWorldTimerManager().SetTimer(TimerHandle_Destroy, this, &AA_Projectile::DestroyProjectile, 5.0f, false);

	
}

void AA_Projectile::DestroyProjectile()
{
	Destroy();
}

void AA_Projectile::SetMaterialF(AActor*ActorValue)
{
	ADroneBasePw* Drone = Cast<ADroneBasePw>(ActorValue);

	if (Drone)
	{
		if(!Drone->IsShield)
		{
			Drone->Mesh->SetMaterial(0,Drone->MainMaterial);
		}
	}
}


// Called every frame
void AA_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_Projectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult)
{
	// Проверяем, является ли OtherActor экземпляром класса DroneBasePw
	ADroneBasePw* Drone = Cast<ADroneBasePw>(OtherActor);
	//ADroneBasePw* Drone = Cast<ADroneBasePw>(OtherActor);
	ATurelBase* Turel = Cast<ATurelBase>(OtherActor);


	if (Drone)
	{
		// Выполняем действия, связанные с DroneBasePw
		// Drone теперь указывает на экземпляр класса DroneBasePw
		//UE_LOG(LogTemp, Warning, TEXT("xxx"));
		//cout<<"damn";
		if(!Drone->IsShield)
		{
			Drone->DamageF(1);
			Drone->Mesh->SetMaterial(0,Drone->DamageMaterial);

			FTimerDelegate TimerCallback;
			TimerCallback.BindLambda([this,Drone]{SetMaterialF(Drone);});
			GetWorldTimerManager().SetTimer(TimerHandle_Material, TimerCallback, 0.2f, false);

		}

	}

	else if (Turel)
	{
		// Если OtherActor не является DroneBasePw, выполните другие действия
		Turel->DamageF(10);
	}
	else if (OtherActor && (OtherActor != this))
	{
		// Если OtherActor не является DroneBasePw, выполните другие действия
	}
	DestroyProjectile();
}
		

// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Projectile.h"
#include "DroneBasePw.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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
		Box->OnComponentHit.AddDynamic(this, &AA_Projectile::OnHit);
	}
	
}

// Called every frame
void AA_Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AA_Projectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								  FVector NormalImpulse, const FHitResult& Hit)
{
	// Проверяем, что OtherComp является экземпляром UBoxComponent
	ADroneBasePw* Dron = Cast<ADroneBasePw>(OtherActor);
	if (Dron)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("хуяк"));

		// Или выполнить другие операции с UBoxComponent
	}
	else
	{
		// OtherComp не является UBoxComponent, выполните другую обработку
	}
}


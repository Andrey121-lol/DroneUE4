// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABoxBase::ABoxBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BoxMesh->SetupAttachment(Box);

	
}

// Called when the game starts or when spawned
void ABoxBase::BeginPlay()
{
	Super::BeginPlay();
	if (Box)
	{
		Box->OnComponentBeginOverlap.AddDynamic(this, &ABoxBase::OnOverlapBegin);
	}
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerPawn = PlayerController->GetPawn();

    	
}

// Called every frame
void ABoxBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxBase::AddResourcesToPlayer(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

}

void ABoxBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADroneBasePw* DroneActor = Cast<ADroneBasePw>(OtherActor);
	if (DroneActor)
	{
		// Если успешно привели к типу ADroneBase, можно вызвать функцию AddResourcesToPlayer
		AddResourcesToPlayer(ValuesResurs);

		// Уничтожаем актер
		Destroy();
	}
}




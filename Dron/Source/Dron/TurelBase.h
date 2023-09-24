// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TurelBase.generated.h"

UCLASS()
class DRON_API ATurelBase : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurelBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BaseTurel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* HeadTurel;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* GunTurel1;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* GunTurel2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	FName BaseTurelParentSocket;

	float SensingRange = 1500;
	float SpeedRotation = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "var")
	AActor* Target ;
	TArray<AActor*> FoundActors;

	
	bool HaslineOfDight(FVector From ,FVector To,TArray<AActor*> ActorsToIgnore);
	void FindTarget();
	void UpdRotation(float DeltaSeconds);

};

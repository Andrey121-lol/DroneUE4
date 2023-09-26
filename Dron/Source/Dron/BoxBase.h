// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DroneBasePw.h"
#include "GameFramework/Actor.h"
#include "BoxBase.generated.h"

UCLASS()
class DRON_API ABoxBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* BoxMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Var")
	APawn* PlayerPawn;

	virtual void AddResourcesToPlayer(float Value);
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep, 
	const FHitResult& SweepResult);

	float ValuesResurs=0;
};

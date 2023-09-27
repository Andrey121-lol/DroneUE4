// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Projectile.h"
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

	float SensingRange = 5000;
	float SpeedRotation = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "var")
	float HP = 100;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "var")
	float FullHP = 100;
	float TimeOfLastFire = 0;
	float RateOfFire = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "var")
	AActor* Target ;
	TArray<AActor*> FoundActors;
	AActor* PlayerPawn = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "var")
	float DotProductValue=0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Var")
	TSubclassOf<AA_Projectile> ProjectileClass;
	bool CanShoot=true;
	bool IsLive=true;
	FTimerHandle MemberTimerHandle1;
	FTimerHandle MemberTimerHandle2;


	
	bool HaslineOfDight(FVector From ,FVector To,TArray<AActor*> ActorsToIgnore);
	void FindTarget();
	void UpdRotation(float DeltaSeconds);
	void DamageF(float Value);
	void Dead();
	void UpdFire();
	FVector GetUnitDirectionVector(FVector StartVector, FVector EndVector);
	float GetDotProductTo(FVector VectorA, FVector VectorB);
	void Fire(class UStaticMeshComponent* Gun);
	void AttackFPres(class UStaticMeshComponent* Gun);
	void AttackFReleas();



};

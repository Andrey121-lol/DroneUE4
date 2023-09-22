// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "E_AnimDrone.h"
#include "A_Projectile.h"
#include "GameOverOrWin_I.h"
#include "DroneBasePw.generated.h"

UCLASS()
class DRON_API ADroneBasePw : public APawn ,public IGameOverOrWin_I
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADroneBasePw();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//vars
	// Box component that will contain the static mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Box2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Box3;

	// Static mesh component that will represent the drone
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

	// Spring arm component that will attach the camera to the mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	// Camera component that will provide the view for the player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* Camera;

	// Объявление переменной типа Class Reference с именем ProjectileClass
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Var")
	TSubclassOf<AA_Projectile> ProjectileClass;



	// Floating pawn movement component that will provide simple movement for the pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Var")
	float FullHP=100;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Var")
	float HP=100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Var")
	int Amo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Var")
	int FullAmo=200;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Var")
	E_AnimDrone AnimDrone;

	bool CanShoot=true;
	
	FTimerHandle MemberTimerHandle;

	//func

	//movement
	void MoveForwardF(float Value);
	void MoveRightF(float Value);
	void MoveUpF(float Value);

	//camera
	void LookRightF(float Value);
	void LookUpF(float Value);

	//attack
	void AttackFPres();
	void Fire();
	void AttackFReleas();
	void Dead();
	void DamageF(float Value);

};

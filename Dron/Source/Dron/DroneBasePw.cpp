// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneBasePw.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"


// Sets default values
ADroneBasePw::ADroneBasePw()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create and attach the box component
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;

	// Create and attach the static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	// Create and attach the spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);

	// Create and attach the camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Create and attach the floating pawn movement component
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->UpdatedComponent = RootComponent;


}

// Called when the game starts or when spawned
void ADroneBasePw::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADroneBasePw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//movement
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Called to bind functionality to input
void ADroneBasePw::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ADroneBasePw::MoveForwardF);
	PlayerInputComponent->BindAxis("MoveRight",this,&ADroneBasePw::MoveRightF);
	PlayerInputComponent->BindAxis("MoveUp",this,&ADroneBasePw::MoveUpF);
	PlayerInputComponent->BindAxis("LookUp",this,&ADroneBasePw::LookUpF);
	PlayerInputComponent->BindAxis("LookRight",this,&ADroneBasePw::LookRightF);
	
}

void ADroneBasePw::MoveForwardF(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector()*Value);

}
void ADroneBasePw::MoveRightF(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector()*Value);

}
void ADroneBasePw::MoveUpF(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorUpVector()*Value);

}

void ADroneBasePw::LookUpF(float Value)
{
	AddControllerPitchInput(Value);
}
void ADroneBasePw::LookRightF(float Value)
{
	AddControllerYawInput(Value);
}
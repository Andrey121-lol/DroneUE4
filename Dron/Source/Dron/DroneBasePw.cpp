// Fill out your copyright notice in the Description page of Project Settings.


#include "DroneBasePw.h"
#include "GameOverOrWin_I.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

template <typename T>
T TAddResurs(T CurrentValue, T MaxValue, T IncrementAmount)
{
	CurrentValue += IncrementAmount;
	if (CurrentValue >= MaxValue)
	{
		CurrentValue = MaxValue;
	}
	return CurrentValue;
}

template <typename T>
T TakeAwayResurs(T CurrentValue, T DecrementAmount,bool&BoolV)
{
	CurrentValue -= DecrementAmount;
	if (CurrentValue < 0)
	{
		CurrentValue = 0;
		BoolV=false;
	}
	
	return CurrentValue;
}


// Sets default values
ADroneBasePw::ADroneBasePw()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Create and attach the box component
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box2 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box2"));
	Box3 = CreateDefaultSubobject<UBoxComponent>(TEXT("Box3"));
	RootComponent = Box;
	
	// Create and attach the static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
	Mesh->SetupAttachment(Box);
	Box2->SetupAttachment(Mesh);
	Box3->SetupAttachment(Mesh);
	
	// Create and attach the spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Mesh);

	// Create and attach the camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Create and attach the floating pawn movement component
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->UpdatedComponent = RootComponent;
	Mesh->SetMaterial(0,MainMaterial);


}

// Called when the game starts or when spawned
void ADroneBasePw::BeginPlay()
{
	Super::BeginPlay();
	//float Angle = 0;
	Mesh->SetMaterial(0,MainMaterial);
}

// Called every frame
void ADroneBasePw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	
	if(AnimDrone==E_AnimDrone::Idle && IfDron)
	{
		FVector NewLocation = GetActorLocation();
		float RunningTime = GetGameTimeSinceCreation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		NewLocation.Z += DeltaHeight * 10.0f;      
		SetActorLocation(NewLocation);
	}

	switch (AnimDrone)
	{
	case E_AnimDrone::Forward:
		Mesh->SetRelativeRotation(FRotator(0,90,0));
		break;
	case E_AnimDrone::Backward:
		Mesh->SetRelativeRotation(FRotator(0,90,15));
		break;
	case E_AnimDrone::Right:
		Mesh->SetRelativeRotation(FRotator(-15,90,0));
		break;
	case E_AnimDrone::Left:
		Mesh->SetRelativeRotation(FRotator(15,90,0));
		break;
	case E_AnimDrone::Idle:
		Mesh->SetRelativeRotation(FRotator(0,90,0));
		break;
	}
	
		

}

// Called to bind functionality to input
void ADroneBasePw::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&ADroneBasePw::MoveForwardF);
	PlayerInputComponent->BindAxis("MoveRight",this,&ADroneBasePw::MoveRightF);
	PlayerInputComponent->BindAxis("MoveUp",this,&ADroneBasePw::MoveUpF);
	PlayerInputComponent->BindAxis("LookUp",this,&ADroneBasePw::LookUpF);
	PlayerInputComponent->BindAxis("LookRight",this,&ADroneBasePw::LookRightF);

	PlayerInputComponent->BindAction("Attack",IE_Pressed,this,&ADroneBasePw::AttackFPres);
	PlayerInputComponent->BindAction("Attack",IE_Released,this,&ADroneBasePw::AttackFReleas);
	PlayerInputComponent->BindAction("Block",IE_Pressed,this,&ADroneBasePw::BlockFPres);
	PlayerInputComponent->BindAction("Block",IE_Released,this,&ADroneBasePw::BlockFReleas);
	
}

void ADroneBasePw::MoveForwardF(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector()*Value);
	
	if(Value>0)
	{
		AnimDrone=E_AnimDrone::Forward;
	}
	else if (Value<0)
	{
		AnimDrone=E_AnimDrone::Backward;
	}
	else if (Value == 0)
	{
		AnimDrone=E_AnimDrone::Idle;
	}
}
void ADroneBasePw::MoveRightF(float Value)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector()*Value);
	
	if(Value>0)
	{
		AnimDrone=E_AnimDrone::Right;
		
	}
	else if (Value<0)
	{
		AnimDrone=E_AnimDrone::Left;
	}
	/*else if (Value == 0)
	{
		AnimDrone=E_AnimDrone::Idle;
	}*/

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

void ADroneBasePw::AttackFPres()
{
	
	if (CanShoot)
	{
		GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ADroneBasePw::Fire, 0.1f, true, 0.1f);
		
	}
}

void ADroneBasePw::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Ваше сообщение здесь"));
	AA_Projectile* SpawnP = GetWorld()->SpawnActor<AA_Projectile>(ProjectileClass,Box2->GetComponentTransform());
	AA_Projectile* SpawnP2 = GetWorld()->SpawnActor<AA_Projectile>(ProjectileClass,Box3->GetComponentTransform());
	Amo=TakeAwayResurs(Amo,one,CanShoot);
	Amo=TakeAwayResurs(Amo,one,CanShoot);
	if(!CanShoot)
	{
		AttackFReleas();
	}


}

void ADroneBasePw::AttackFReleas()
{
	GetWorldTimerManager().ClearTimer(MemberTimerHandle);

}

void ADroneBasePw::Dead()
{
	IGameOverOrWin_I* InterfaceImplementer = Cast<IGameOverOrWin_I>(this);

	if (InterfaceImplementer)
	{
		InterfaceImplementer->Execute_GameOverF(this);
	}

}

void ADroneBasePw::BlockFPres()
{
	if (CanShield)
	{
		IsShield=true;
		FTimerDelegate TimerCallBack;
		TimerCallBack.BindLambda([this]()
		{
			RemoveShield(10);
		});
	
		GetWorldTimerManager().SetTimer(MemberTimerHandle2, TimerCallBack, 0.1f, true, 0.1f);

		Mesh->SetMaterial(0,ShieldMaterial);
		
		
	}
}

void ADroneBasePw::BlockFReleas()
{
	IsShield=false;
	Mesh->SetMaterial(0,MainMaterial);
	GetWorldTimerManager().ClearTimer(MemberTimerHandle2);


}

void ADroneBasePw::DamageF(float Value)
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

void ADroneBasePw::AddHP(float Value)
{
	HP=TAddResurs(HP,FullHP,Value);
	
}

void ADroneBasePw::AddAmo(float Value)
{
	Amo=TAddResurs(Amo,FullAmo,Value);

}

void ADroneBasePw::AddShield(float Value)
{
	Shield=TAddResurs(Shield,FullShield,Value);

}

void ADroneBasePw::RemoveShield(float Value)
{
	Shield=TakeAwayResurs(Shield,Value,CanShield);
	if (!CanShield)
	{
		BlockFReleas();
	}
	
}


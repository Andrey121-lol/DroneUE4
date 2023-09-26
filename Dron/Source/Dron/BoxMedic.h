// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxBase.h"
#include "BoxMedic.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ABoxMedic : public ABoxBase
{
	GENERATED_BODY()
	virtual void AddResourcesToPlayer(float Value) override;

};

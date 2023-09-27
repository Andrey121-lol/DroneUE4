// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoxBase.h"
#include "BoxWin.generated.h"

/**
 * 
 */
UCLASS()
class DRON_API ABoxWin : public ABoxBase
{
	GENERATED_BODY()

	virtual void Tick(float DeltaTime) override;
	virtual void AddResourcesToPlayer(float Value);

	
	
};

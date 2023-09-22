// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameOverOrWin_I.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameOverOrWin_I : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DRON_API IGameOverOrWin_I
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Func")
	void GameOverF();
    
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Func")
	void GameWinF();
    
	virtual void GameOverF_Implementation()
	{
		// C++ implementation of GameOver
	}

	virtual void GameWinF_Implementation()
	{
		// C++ implementation of GameWin
	}
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "World/ChefWithPawsGameMode.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API AMenuGameMode : public AChefWithPawsGameMode
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartGame();
	
	
};

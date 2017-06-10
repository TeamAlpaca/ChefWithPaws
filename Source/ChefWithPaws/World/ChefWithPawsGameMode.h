// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameModeBase.h"
#include "ChefWithPawsGameMode.generated.h"

UCLASS(minimalapi)
class AChefWithPawsGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AChefWithPawsGameMode();
	
	virtual void InitGameState()override;
	void FinishGame();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> EndingWidgetClass;
	
	UPROPERTY()
		UUserWidget* CurrentWidget;

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UFUNCTION(BlueprintPure, Category = "Coin")
		int32 GetCoin()const;

	UFUNCTION(BlueprintPure, Category = "Coin")
		int32 GetCountdownTime()const;


	void AdvanceTimer();

	UFUNCTION(BlueprintCallable, Category = "Strat")
	void StartNow();

	UFUNCTION(BlueprintCallable, Category = "Quit")
		void ReturnToMenu();

protected:

UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coin", Meta = (BlueprintProtected = "true"))
		int32 CountdownTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Coin", Meta = (BlueprintProtected = "true"))
		int32 Coin;

	UPROPERTY(EditAnywhere)
		int32 ReadinessTime;
	FTimerHandle ReadinessTimerHandle;

	FTimerHandle CountdownTimerHandle;


};




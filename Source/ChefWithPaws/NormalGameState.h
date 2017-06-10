// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "NormalGameState.generated.h"


UENUM(BlueprintType)
enum class ENomalGameplayState:uint8
{
	EWaiting UMETA(DisplayName = "Waiting"),
	EPlaying UMETA(DisplayName = "Playing"),
	EPause UMETA(DisplayName = "Pause"),
	EFinish UMETA(DisplayName = "Finish"),
};

UCLASS()
class CHEFWITHPAWS_API ANormalGameState : public AGameState
{
	GENERATED_BODY()
private:
	ENomalGameplayState GameplayState;
	
public:
	void	StartGameplayStateMachine();

	ENomalGameplayState GetGameplayState()const;

	void SetGameplayState(ENomalGameplayState NewState);

	UFUNCTION(BlueprintCallable, Category = "Game State")
		bool IsWaiting();
	UFUNCTION(BlueprintCallable, Category = "Game State")
	bool IsPlaying();

	
};

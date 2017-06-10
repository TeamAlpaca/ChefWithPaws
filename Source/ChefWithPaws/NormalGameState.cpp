// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "NormalGameState.h"

void	ANormalGameState::StartGameplayStateMachine()
{
	GameplayState = ENomalGameplayState::EWaiting;
}

ENomalGameplayState ANormalGameState::GetGameplayState() const
{
	return GameplayState;
}

void ANormalGameState::SetGameplayState(ENomalGameplayState NewState)
{
	GameplayState=NewState;
}
bool ANormalGameState::IsWaiting()
{
	return GameplayState == ENomalGameplayState::EWaiting;
}

bool ANormalGameState::IsPlaying()
{
	return GameplayState == ENomalGameplayState::EPlaying;
}


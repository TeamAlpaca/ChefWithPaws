// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChefWithPaws.h"
#include "ChefWithPawsGameMode.h"
#include "ChefWithPawsCharacter.h"
#include "NormalGameState.h"


AChefWithPawsGameMode::AChefWithPawsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = ANormalGameState::StaticClass();


}


void AChefWithPawsGameMode::InitGameState()
{
	Super::InitGameState();
	UE_LOG(LogTemp, Error, TEXT("InitGameState"));
	ChangeMenuWidget(StartingWidgetClass);
	Coin = 0;
	ANormalGameState* const NormalGameState = GetGameState<ANormalGameState>();
	check(NormalGameState);
	NormalGameState->StartGameplayStateMachine();
}
int32 AChefWithPawsGameMode::GetCountdownTime() const
{
	return CountdownTime;
}


void AChefWithPawsGameMode::StartNow()
{
	UE_LOG(LogTemp, Error, TEXT("StartNow"));
	AChefWithPawsCharacter* Character = Cast<AChefWithPawsCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Character->SetupPlayerInputComponentNow();
	CountdownTime = 100;
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AChefWithPawsGameMode::AdvanceTimer, 1.0f, true);
	ANormalGameState* const NormalGameState = GetGameState<ANormalGameState>();
	check(NormalGameState);
	NormalGameState->SetGameplayState(ENomalGameplayState::EPlaying);
}

void AChefWithPawsGameMode::ReturnToMenu()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/main"));
}

void AChefWithPawsGameMode::AdvanceTimer()
{
	--CountdownTime;
	if (CountdownTime < 1)
	{
		// 倒计时结束，停止运行定时器。
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//在定时器结束时按需要执行特殊操作。
		FinishGame();
	}
	
}

void AChefWithPawsGameMode::FinishGame()
{
	ChangeMenuWidget(EndingWidgetClass);
	ANormalGameState* const NormalGameState = GetGameState<ANormalGameState>();
	check(NormalGameState);
	NormalGameState->SetGameplayState(ENomalGameplayState::EFinish);
}

void AChefWithPawsGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
int32 AChefWithPawsGameMode::GetCoin() const
{
	return Coin;
}
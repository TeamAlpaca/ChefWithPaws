// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChefWithPaws.h"
#include "ChefWithPawsGameMode.h"
#include "ChefWithPawsCharacter.h"
#include "NormalWidget.h"
#include "OrderList.h"



AChefWithPawsGameMode::AChefWithPawsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	GameStateClass = AOrderList::StaticClass();
	
}

void  AChefWithPawsGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Error, TEXT("InitGameState"));
	ChangeMenuWidget(StartingWidgetClass);
	AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
	check(OrderList);
	OrderList->StartGameplayStateMachine();
	SetGameplayState(ENomalGameplayState::EWaiting);
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
	SetGameplayState(ENomalGameplayState::EPlaying);

	Coin = 0;
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
		// ����ʱ������ֹͣ���ж�ʱ����
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		//�ڶ�ʱ������ʱ����Ҫִ�����������
		FinishGame();
	}
	if (CountdownTime%5==0)
	{
		AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
		check(OrderList);
		OrderList->CreateNewOrder();
		UE_LOG(LogTemp, Error, TEXT("Order"));
	}
	
}

void AChefWithPawsGameMode::FinishGame()
{
	UNormalWidget*Widget = Cast<UNormalWidget>(CurrentWidget);
	check(Widget);
	Widget->Stop();
	AOrderList* OrderList = Cast<AOrderList>(GetWorld()->GetGameState());
	check(OrderList);
	OrderList->Stop();
	ChangeMenuWidget(EndingWidgetClass);
	SetGameplayState(ENomalGameplayState::EFinish);
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




ENomalGameplayState AChefWithPawsGameMode::GetGameplayState() const
{
	return GameplayState;
}

void AChefWithPawsGameMode::SetGameplayState(ENomalGameplayState NewState)
{
	GameplayState = NewState;
}
bool AChefWithPawsGameMode::IsWaiting()
{
	return GameplayState == ENomalGameplayState::EWaiting;
}

bool AChefWithPawsGameMode::IsPlaying()
{
	return GameplayState == ENomalGameplayState::EPlaying;
}

int32 AChefWithPawsGameMode::GetCoin() const
{
	return Coin;
}

void AChefWithPawsGameMode::AddCoin(int32 Number)
{
	Coin = Coin + Number;
}

void AChefWithPawsGameMode::MinusCoin(int32 Number)
{
	Coin = Coin - Number;
}

void  AChefWithPawsGameMode::Return()
{
	GetWorld()->ServerTravel(FString("/Game/Maps/main"));
}
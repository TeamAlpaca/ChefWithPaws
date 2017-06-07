// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "MainMenuGameMode.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(StartingWidgetClass);
}
void AMainMenuGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
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

void AMainMenuGameMode::StartGame()
{
		GetWorld()->ServerTravel(FString("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap"));
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuGameMode.generated.h"


 
 
UCLASS()
class CHEFWITHPAWS_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
 
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
		void StartGame();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
		UUserWidget* CurrentWidget;

};

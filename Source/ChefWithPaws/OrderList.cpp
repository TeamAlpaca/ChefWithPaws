// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "OrderList.h"
#include "World/ChefWithPawsGameMode.h"
#include "NormalWidget.h"



void AOrderList::StartGameplayStateMachine()
{
	for (int32 i = 0; i != 5; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		List.Emplace( GetWorld()->SpawnActor<AOrder>(SpawnInfo));
		List[i]->SetSlot(i);
		UE_LOG(LogTemp, Error, TEXT("set order"));
	}
	Finished = 0;
	Missed = 0;
}

int32 AOrderList::GetMissed()
{
	return Missed;
}

void AOrderList::CreateNewOrder()
{	
	UE_LOG(LogTemp, Error, TEXT("Create"));
	for (int32 i = 0; i < List.Num(); i++)
	{
		if (List[i]->GetType() == 0)
		{
			
			List[i]->CreateNewOrder();
			break;
		}
	}
}

void AOrderList::Stop()
{
	for (auto val : List)
	{
		if (val->GetType())
		{
		val->StopCountdown();
		}
	}
}

int32 AOrderList::GetCountdownTime(int32 i)
{
	return List[i]->GetCountdownTime();
}

int32 AOrderList::GetFinished()
{
	return Finished;
}

void AOrderList::CheckFood(FString ID)
{
	for (auto val : List)
	{
		if (ID == val->GetFoodID())
		{
			val->Finish();
			break;
		}
	}
}
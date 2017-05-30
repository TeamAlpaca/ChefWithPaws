// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHEFWITHPAWS_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTriggerComponent();
	// Called when the game starts

	AActor* OtherActor;

	/** 当某对象进入box组件时调用 */
	UFUNCTION()

		void OnOverlapBegin(AActor * Self, AActor* Target, FVector direction);

	/** 当某对象离开box组件时调用 */
	UFUNCTION()
		void OnOverlapEnd();

	//组件成员们

	UInputComponent* InputComponent = nullptr;

	// Setup (assumed) attached input component安装输入组件
	void SetupInputComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);
	void Grab();

	// Called when grab is released释放
	void Release();
	FVector GetReachLineEnd();
	bool Grabbed;
};

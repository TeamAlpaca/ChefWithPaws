// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/BoxComponent.h"
#include "Grabber.generated.h"

/**
*
*/
UCLASS()
class CHEFWITHPAWS_API UGrabber : public UBoxComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();
	// Called when the game starts

	AActor* OtherActor;

	/** 当某对象进入box组件时调用 */
	UFUNCTION()

		void OnOverlapBegin(AActor * Self, AActor* Target);

	/** 当某对象离开box组件时调用 */
	UFUNCTION()
		void OnOverlapEnd();

	//组件成员们
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	// Setup (assumed) attached input component安装输入组件
	void SetupInputComponent();
	void FindPhysicsHandleComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);
	void GrabOrRelease();
	void Grab();
	void Release();
	FVector GetReachLineEnd();
	FVector Direction;
	bool Grabbed;
};

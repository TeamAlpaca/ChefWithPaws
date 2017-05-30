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
public:
	/** ��ĳ�������box���ʱ���� */
	UFUNCTION()
   void OnOverlapBegin(AActor * Self, AActor* Target);

	/** ��ĳ�����뿪box���ʱ���� */
	UFUNCTION()
		 void OnOverlapEnd();

	//�����Ա��

	UInputComponent* InputComponent = nullptr;

	// Setup (assumed) attached input component��װ�������
 void SetupInputComponent();
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction);
	void Grab();

	// Called when grab is released�ͷ�
	void Release();
	FVector GetReachLineEnd();
	void SetLocation();
	bool Grabbed;
};

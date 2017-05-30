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

	/** ��ĳ�������box���ʱ���� */
	UFUNCTION()

		void OnOverlapBegin(AActor * Self, AActor* Target, FVector direction);

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
	bool Grabbed;
};

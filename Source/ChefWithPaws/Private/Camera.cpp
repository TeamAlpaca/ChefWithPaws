// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "Camera.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACamera::ACamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (OurPlayerController)
	{
		if ((OurPlayerController->GetViewTarget() != CameraOne) && (CameraOne != nullptr))
		{
			// 立即切换到相机1。
			OurPlayerController->SetViewTarget(CameraOne);
		}
	}
}


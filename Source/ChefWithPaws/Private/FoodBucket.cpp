// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "FoodBucket.h"


// Sets default values
AFoodBucket::AFoodBucket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	/*PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxComponent;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;
	BoxComponent->InitBox;
	BoxComponent->SetCollisionProfileName(TEXT("Plate"));*/
}

// Called when the game starts or when spawned
void AFoodBucket::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodBucket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


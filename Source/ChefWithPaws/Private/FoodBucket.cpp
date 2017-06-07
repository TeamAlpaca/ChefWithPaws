// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "FoodBucket.h"
#include "FoodCabbage.h"


// Sets default values
AFoodBucket::AFoodBucket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.


	PrimaryActorTick.bCanEverTick = true;


	BucketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BucketMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>BucketAsset(TEXT("/Game/Food/Bucket"));
	if (BucketAsset.Succeeded())
	{
		BucketMesh->SetStaticMesh(BucketAsset.Object);
		BucketMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		BucketMesh->SetWorldScale3D(FVector(1.0f));
	}

	BucketMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootComponent = BucketMesh;
	BucketMesh->Mobility = EComponentMobility::Static;

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

void AFoodBucket::ApawnActor()
{
	FVector NewLocation = GetActorLocation() + FVector(0.f, 0.f, 50.f);
	AFoodCabbage* NewFood;
	NewFood = (AFoodCabbage*)GetWorld()->SpawnActor(AFoodCabbage::StaticClass(), &NewLocation);
}



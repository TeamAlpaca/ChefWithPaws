// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "FoodCabbage.h"


// Sets default values
AFoodCabbage::AFoodCabbage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
		RootComponent = SphereComponent;
		SphereComponent->InitSphereRadius(30.0f);
		SphereComponent->SetCollisionProfileName(TEXT("Sphere"));
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CabbageAsset(TEXT("/Game/Food/Cabbage"));
	if (CabbageAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(CabbageAsset.Object);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		MeshComponent->SetWorldScale3D(FVector(1.0f));
	}
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->bGenerateOverlapEvents = true;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetSimulatePhysics(true);
	MeshComponent->SetEnableGravity(true);
	
	SphereComponent->Mobility= EComponentMobility::Movable;
	
}

// Called when the game starts or when spawned
void AFoodCabbage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFoodCabbage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


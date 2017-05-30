// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "TriggerComponent.h"


UTriggerComponent::UTriggerComponent()
{

	PrimaryComponentTick.bCanEverTick =true; //true就每帧都调用
	OtherActor = nullptr;
}



void UTriggerComponent::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{                                                       //↓输入时调用grab
		InputComponent->BindAction("Grab", IE_Pressed, this, &UTriggerComponent::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UTriggerComponent::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}


void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!Grabbed) { return; }
	FVector Location= OtherActor->GetActorLocation();
		OtherActor->SetActorLocationAndRotation(FVector(GetReachLineEnd().X, GetReachLineEnd().Y, Location.Z), GetOwner()->GetActorRotation(),true);
		
}
void UTriggerComponent::Grab()
{
	if(!OtherActor) { return; }
    auto ComponentToGrab = Cast<UStaticMeshComponent>(OtherActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (ComponentToGrab)
	{
		ComponentToGrab->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		ComponentToGrab->SetSimulatePhysics(false);
		
		FVector Location = OtherActor->GetActorLocation();
		OtherActor->SetActorLocation(FVector(Location.X, Location.Y, 230.0f));
		Grabbed = true;
		OtherActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}
void UTriggerComponent::Release()
{
	if (!OtherActor) { return; }
	if (!Grabbed) { return; }
	auto ComponentToGrab = Cast<UStaticMeshComponent>(OtherActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	if (ComponentToGrab)
	{
		ComponentToGrab->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ComponentToGrab->SetSimulatePhysics(true);
	
		Grabbed = false;
		OtherActor->GetRootComponent()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}
FVector UTriggerComponent::GetReachLineEnd()
{
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	FVector Location = FVector(PlayerLocation.X, PlayerLocation.Y, 0);
	FVector Rotation = FVector(GetOwner()->GetActorRotation().Vector());

	return PlayerLocation + Rotation*75;
}
void UTriggerComponent::OnOverlapBegin(AActor * Self, AActor * Target, FVector direction)
{
	OtherActor = Target;
	SetupInputComponent();
}

void UTriggerComponent::OnOverlapEnd()
{
	OtherActor = nullptr;
}


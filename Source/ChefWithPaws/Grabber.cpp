// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "Grabber.h"


UGrabber::UGrabber()
{    

	PrimaryComponentTick.bCanEverTick = true; //true就每帧都调用
	OtherActor = nullptr;
	Grabbed = false;
}



void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{                                                       //↓输入时调用grab
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabOrRelease);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UGrabber::FindPhysicsHandleComponent()
{    //↓自己定义的一个成员   物理组件
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//↑使一个actor拥有他 返回其指针 
	//AActor::FindComponentByClass  一个模板，搜索组件数组并返回指定类的第一个遇到的组件。
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *OtherActor->GetName())
	}
}
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	//↓目前搜索到了一个handle   并持有的组件
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		//ENGINE_API void SetTargetLocation(FVectorNEW! NewLocation)
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
void UGrabber::GrabOrRelease()
{
	if (Grabbed) { Release(); }
	else { Grab(); }
}

void UGrabber::Grab()
{
	TArray<UMeshComponent*> Components;
	OtherActor->GetComponents<UMeshComponent>(Components);
	if (Components.Num() == 0) { return; }
	auto ComponentToGrab = Components[0];
	if (!PhysicsHandle) { return; }
	//前面的grabcomponent是个class，这里是个函数
	//virtual ENGINE_API void GrabComponent(class UPrimitiveComponentNEW! * Component,FNameNEW!InBoneName,FVectorNEW! GrabLocation,bool bConstrainRotation)
	//抓住

	PhysicsHandle->GrabComponent(
		ComponentToGrab,
		NAME_None, // no bones needed
		ComponentToGrab->GetOwner()->GetActorLocation(),
		true // allow rotation
	);
	Grabbed = true;
}
void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
	Grabbed = false;
}
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerViewPointLocation = GetOwner()->GetActorLocation();
	PlayerViewPointRotation = GetOwner()->GetActorRotation();
	return PlayerViewPointLocation + (PlayerViewPointRotation.Vector())  * 80.0f;
}
void UGrabber::OnOverlapBegin(AActor * Self, AActor * Target)
{
	OtherActor = Target;
	FindPhysicsHandleComponent();
	SetupInputComponent();	
}

void UGrabber::OnOverlapEnd()
{
	OtherActor = nullptr;
}

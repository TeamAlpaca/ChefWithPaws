// Fill out your copyright notice in the Description page of Project Settings.

#include "ChefWithPaws.h"
#include "Grabber.h"


UGrabber::UGrabber()
{    

	PrimaryComponentTick.bCanEverTick = true; //true��ÿ֡������
	OtherActor = nullptr;
}



void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{                                                       //������ʱ����grab
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UGrabber::FindPhysicsHandleComponent()
{    //���Լ������һ����Ա   �������
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	//��ʹһ��actorӵ���� ������ָ�� 
	//AActor::FindComponentByClass  һ��ģ�壬����������鲢����ָ����ĵ�һ�������������
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
	//��Ŀǰ��������һ��handle   �����е����
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		//ENGINE_API void SetTargetLocation(FVectorNEW! NewLocation)
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}
void UGrabber::Grab()
{
	TArray<UMeshComponent*> Components;
	OtherActor->GetComponents<UMeshComponent>(Components);
	if (Components.Num() == 0) { return; }
	auto ComponentToGrab = Components[0];
	if (!PhysicsHandle) { return; }
	//ǰ���grabcomponent�Ǹ�class�������Ǹ�����
	//virtual ENGINE_API void GrabComponent(class UPrimitiveComponentNEW! * Component,FNameNEW!InBoneName,FVectorNEW! GrabLocation,bool bConstrainRotation)
	//ץס

	PhysicsHandle->GrabComponent(
		ComponentToGrab,
		NAME_None, // no bones needed
		ComponentToGrab->GetOwner()->GetActorLocation(),
		true // allow rotation
	);
}
void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
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

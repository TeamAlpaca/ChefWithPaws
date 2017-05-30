// Fill out your copyright notice in the Description page of Project Settings.
 #include "ChefWithPaws.h"
  #include "Grabber.h"
 
 
 UGrabber::UGrabber()
  {
	 
		 PrimaryComponentTick.bCanEverTick = true; //true就每帧都调用
	 OtherActor = nullptr;
	 }
 
 
 
 void UGrabber::SetupInputComponent()
  {
	 InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	 if (InputComponent)
		 {                                                       //↓输入时调用grab
		 InputComponent ->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		 InputComponent ->BindAction("Grab", IE_Released, this, &UGrabber::Release);
		 }
	 else
		  {
		 UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner() ->GetName())
			  }
	 }
 
 
 void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
  {
	 Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	 if (!Grabbed) { return; }
	 FVector Location = OtherActor ->GetActorLocation();
	 OtherActor ->SetActorLocationAndRotation(FVector(GetReachLineEnd().X, GetReachLineEnd().Y, Location.Z), GetOwner() ->GetActorRotation(), true);
	  }
 void UGrabber::Grab()
  {
	 if (!OtherActor) { return; }
	 if (Grabbed) { return; }
	 auto ComponentToGrab = Cast<UStaticMeshComponent>(OtherActor ->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	 if (ComponentToGrab)
		 {
		 ComponentToGrab ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		 ComponentToGrab ->SetSimulatePhysics(false);
		 ComponentToGrab->SetEnableGravity(false);
			 FVector Location = OtherActor->GetActorLocation();
		 OtherActor ->SetActorLocation(FVector(Location.X, Location.Y, 230.0f),true);
		 Grabbed = true;
		 OtherActor ->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		 }
	 }
 void UGrabber::Release()
  {
	 if (!OtherActor) { return; }
	 if (!Grabbed) { return; }
	 auto ComponentToGrab = Cast<UStaticMeshComponent>(OtherActor ->GetComponentByClass(UStaticMeshComponent::StaticClass()));
	 if (ComponentToGrab)
		 {
		 ComponentToGrab ->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		 ComponentToGrab ->SetSimulatePhysics(true);
		 ComponentToGrab->SetEnableGravity(true);			 
		 Grabbed = false;
		 OtherActor ->GetRootComponent() ->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		 }
	 }
 FVector UGrabber::GetReachLineEnd()
  {
	 const FVector PlayerLocation = GetOwner() ->GetActorLocation();
	 FVector Location = FVector(PlayerLocation.X, PlayerLocation.Y, 0);
	 FVector Rotation = FVector(GetOwner() ->GetActorRotation().Vector());
	 
		 return PlayerLocation + Rotation * 75;
	 }
 void UGrabber::OnOverlapBegin(AActor * Self, AActor * Target)
  {
	 OtherActor = Target;
	 SetupInputComponent();
	 }

void UGrabber::OnOverlapEnd()
{
	OtherActor = nullptr;
	}
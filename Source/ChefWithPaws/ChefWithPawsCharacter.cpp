// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ChefWithPaws.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "ChefWithPawsCharacter.h"
#include "Grabber.h"


//////////////////////////////////////////////////////////////////////////
// AChefWithPawsCharacter

AChefWithPawsCharacter::AChefWithPawsCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	PhysicsHandle = ObjectInitializer.CreateDefaultSubobject<UPhysicsHandleComponent>(this, TEXT("PhysicsHandle"));

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->bEnableCameraLag = true;
	// Create a topdown camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm*/
	Grabber = ObjectInitializer.CreateDefaultSubobject<UGrabber>(this, TEXT("Trigger"));
	//重叠盒尺寸
	Grabber->InitBoxExtent(FVector(50.0f, 30.0f, 100.0f));
	Grabber->SetRelativeLocation(FVector(30.0f, 0.0f, 0.0f));
	Grabber->SetupAttachment(RootComponent);

	Grabber->OnComponentBeginOverlap.AddDynamic(this, &AChefWithPawsCharacter::OnOverlapBegin);       // 当此组件与某对象重叠时，设置通知
	Grabber->OnComponentEndOverlap.AddDynamic(this, &AChefWithPawsCharacter::OnOverlapEnd);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AChefWithPawsCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AChefWithPawsCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChefWithPawsCharacter::MoveRight);

}

void AChefWithPawsCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AChefWithPawsCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void AChefWithPawsCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (!OtherActor->IsRootComponentMovable()) { return; }
		Grabber->OnOverlapBegin(this, OtherActor);
	}
}

void AChefWithPawsCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	Grabber->OnOverlapEnd();
}


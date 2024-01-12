// Fill out your copyright notice in the Description page of Project Settings.


#include "BallCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainGameInstance.h"
#include "Misc/App.h"

// Sets default values
ABallCharacter::ABallCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = SphereMesh;
	SphereMesh->SetSimulatePhysics(true);
	SphereMesh->SetEnableGravity(false);

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera
}

// Called when the game starts or when spawned
void ABallCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateGravityDirection();
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, (Gravity * CameraBoom->GetUpVector()).ToString());
	
}

void ABallCharacter::TiltAction(float Val)
{
	//Cast<UMainGameInstance>(GetGameInstance())->TiltInputEvent.Broadcast(Val);
	FRotator curRot = CameraBoom->GetRelativeRotation();
	curRot = FRotator(0, 0, FMath::ClampAngle(curRot.Roll+ Val * FApp::GetDeltaTime() * RotateSpd, -15.0f, 15.0f));
	//CameraBoom->AddRelativeRotation(FRotator(0, 0, Val * FApp::GetDeltaTime()* RotateSpd));
	CameraBoom->SetRelativeRotation(curRot);
	UpdateGravityDirection();
}

void ABallCharacter::JumpAction()
{
	if (!canJump)return;
	canJump = false;
	SphereMesh->AddImpulse(-GravityDirection* JumpForce,"", true);
	FTimerHandle timeerhandle;
	GetWorld()->GetTimerManager().SetTimer(timeerhandle, [&]()
		{
			canJump = true;
		}, 3.0f, false);
}

void ABallCharacter::UpdateGravityDirection()
{
	GravityDirection = -CameraBoom->GetUpVector();
}

// Called every frame
void ABallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SphereMesh->SetPhysicsLinearVelocity(Gravity * GravityDirection, true);
}

// Called to bind functionality to input
void ABallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABallCharacter::TiltAction);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallCharacter::JumpAction);
}


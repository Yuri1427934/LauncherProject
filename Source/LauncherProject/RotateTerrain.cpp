// Fill out your copyright notice in the Description page of Project Settings.


#include "RotateTerrain.h"
#include "Kismet/GameplayStatics.h"
#include "MainGameInstance.h"
// Sets default values
ARotateTerrain::ARotateTerrain()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = MainMesh;
	MainMesh->SetSimulatePhysics(true);
	MainMesh->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ARotateTerrain::BeginPlay()
{
	Super::BeginPlay();
	auto _ins = Cast<UMainGameInstance>(GetGameInstance());
	if (_ins != NULL)
	{
		_ins->TiltInputEvent.AddUniqueDynamic(this, &ARotateTerrain::TiltAction);
	}
}



// Called every frame
void ARotateTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurTick = DeltaTime;
}

// Called to bind functionality to input
void ARotateTerrain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Display, TEXT("AddingInput"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARotateTerrain::TiltAction(float Val)
{
	UE_LOG(LogTemp, Display, TEXT("AAA"));
	AddActorLocalRotation(FRotator(0,0, -Val * CurTick * 10.0f));
	SetActorRotation(FRotator(0, 0, FMath::ClampAngle(GetActorRotation().Roll, -5.0f, 5.0f)));
	//MainMesh->AddAngularImpulse(FVector(0, -Val * CurTick, 0));
}


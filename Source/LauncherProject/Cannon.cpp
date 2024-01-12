// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/SphereComponent.h"
#include "BallCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerControllerInterface.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootMesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root"));
	RootComponent = rootMesh;
	CollisionArea = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionArea"));
	CollisionArea->SetupAttachment(RootComponent);
	CollisionArea->OnComponentBeginOverlap.AddDynamic(this, &ACannon::OnOverlapBegin);

	loadPos = CreateDefaultSubobject<USceneComponent>(TEXT("LoadPos"));
	CollisionArea->SetupAttachment(RootComponent);
	loadPos->SetRelativeLocation(FVector::ZeroVector);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACannon::Fire()
{
	if (!playerRef)return;
	playerRef->ApplyForce(this->GetActorUpVector()*5000.0f);
	playerRef->StartMovement();
	if (PlayerController)
	{
		PlayerController->GetJumpPressEvent()->RemoveAll(this);
	}
	FTimerHandle timeerhandle;
	GetWorld()->GetTimerManager().SetTimer(timeerhandle, [&]()
		{
			IsPlayerIn = false;
		}, 3.0f, false);
}

void ACannon::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPlayerIn)return;
	if (Cast<ABallCharacter>(OtherActor))
	{
		IsPlayerIn = true;
		playerRef = Cast<ABallCharacter>(OtherActor);
		
		playerRef->SetActorLocation(loadPos->GetComponentLocation());
		playerRef->StopMovement();
		if (!PlayerController)
		{
			PlayerController = Cast<IPlayerControllerInterface>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		}
		if (PlayerController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "In!");
			PlayerController->GetJumpPressEvent()->AddUObject(this, &ACannon::Fire);
		}
	}
	
}


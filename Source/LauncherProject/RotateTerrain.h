// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RotateTerrain.generated.h"

UCLASS()
class LAUNCHERPROJECT_API ARotateTerrain : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MainMesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MainMesh;

public:
	// Sets default values for this pawn's properties
	ARotateTerrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void TiltAction(float Val);

	float CurTick=0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

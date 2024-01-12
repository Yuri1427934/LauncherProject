// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BallCharacter.generated.h"

UCLASS()
class LAUNCHERPROJECT_API ABallCharacter : public APawn
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MainMesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SphereMesh;

public:
	// Sets default values for this pawn's properties
	ABallCharacter();

	UPROPERTY(EditAnywhere)
		float Gravity = 9.8f;
	UPROPERTY(EditAnywhere)
		float RotateSpd = 10.0f;
	UPROPERTY(EditAnywhere)
		float JumpForce = 500.0f;

	bool canJump=true;

	FVector GravityDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void TiltAction(float Val);

	void JumpAction();

	void UpdateGravityDirection();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

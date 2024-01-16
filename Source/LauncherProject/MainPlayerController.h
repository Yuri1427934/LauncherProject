// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerInterface.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LAUNCHERPROJECT_API AMainPlayerController : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()
public:
	void PressJump();

protected:
	virtual void SetupInputComponent() override;
	virtual FJumpPressEvent* GetJumpPressEvent() override;
private:
	FJumpPressEvent JumpPressEvent;
};

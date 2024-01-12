// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

void AMainPlayerController::PressJump()
{
    JumpPressEvent.Broadcast();
}

void AMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayerController::PressJump);
}

FJumpPressEvent* AMainPlayerController::GetJumpPressEvent()
{
    return &JumpPressEvent;
}

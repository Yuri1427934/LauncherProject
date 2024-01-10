// Copyright Epic Games, Inc. All Rights Reserved.

#include "LauncherProjectGameMode.h"
#include "LauncherProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALauncherProjectGameMode::ALauncherProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "RemakeCharacterAnimGameMode.h"
#include "RemakeCharacterAnimCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARemakeCharacterAnimGameMode::ARemakeCharacterAnimGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "Clean_InventoryGameMode.h"
#include "Clean_InventoryCharacter.h"
#include "UObject/ConstructorHelpers.h"

AClean_InventoryGameMode::AClean_InventoryGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

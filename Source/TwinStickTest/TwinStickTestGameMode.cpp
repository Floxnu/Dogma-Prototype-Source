// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TwinStickTestGameMode.h"
#include "TwinStickTestPawn.h"

ATwinStickTestGameMode::ATwinStickTestGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ATwinStickTestPawn::StaticClass();
}


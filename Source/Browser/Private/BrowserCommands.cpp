// Copyright Epic Games, Inc. All Rights Reserved.

#include "BrowserCommands.h"

#define LOCTEXT_NAMESPACE "FBrowserModule"

void FBrowserCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Browser", "Bring up Browser window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE

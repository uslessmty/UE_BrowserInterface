// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BrowserStyle.h"

class FBrowserCommands : public TCommands<FBrowserCommands>
{
public:

	FBrowserCommands()
		: TCommands<FBrowserCommands>(TEXT("Browser"), NSLOCTEXT("Contexts", "Browser", "Browser Plugin"), NAME_None, FBrowserStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};
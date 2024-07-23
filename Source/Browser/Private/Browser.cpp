// Copyright Epic Games, Inc. All Rights Reserved.

#include "Browser.h"
#include "BrowserStyle.h"
#include "BrowserCommands.h"
#include "LocalBrowser.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include"STestEditorViewport.h"

static const FName BrowserTabName("Browser");

#define LOCTEXT_NAMESPACE "FBrowserModule"

void FBrowserModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FBrowserStyle::Initialize();
	FBrowserStyle::ReloadTextures();

	FBrowserCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBrowserCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBrowserModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBrowserModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BrowserTabName, FOnSpawnTab::CreateRaw(this, &FBrowserModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBrowserTabTitle", "Browser"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FBrowserModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBrowserStyle::Shutdown();

	FBrowserCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BrowserTabName);
}

TSharedRef<SDockTab> FBrowserModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	
	auto tab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SOverlay)
			+SOverlay::Slot()
			[
				SNew(STestEditorViewport)
			]
			+SOverlay::Slot()
			[
				SNew(SLocalBrowser)
					.InitialURL(TEXT("http://localhost:5173/"))
					.FrameRate(60)
					.EnableMouseTransparency(true)
					.MouseTransparencyThreshold(0.33)
					.MouseTransparencyDelay(0.01)
			]
		];

	
	return tab;
}

void FBrowserModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(BrowserTabName);
}

void FBrowserModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBrowserCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBrowserCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBrowserModule, Browser)
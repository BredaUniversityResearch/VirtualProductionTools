// Copyright Epic Games, Inc. All Rights Reserved.

#include "CradleLightControl.h"

#include "CentralLightController.h"
#include "LevelEditor.h"
#include "LightControlTool.h"


// Test code for a plugin, mainly trying to get an editor window which can be customized using the Slate Framework
// Don't mind the extra debug-y prints and text pieces

#define LOCTEXT_NAMESPACE "FCradleLightControlModule"

void FCradleLightControlModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.NotifyCustomizationModuleChanged();

	auto& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");

	CommandList = MakeShareable(new FUICommandList);
	TSharedRef<FExtender> MenuExtender(new FExtender());
	MenuExtender->AddMenuExtension("EditMain", EExtensionHook::After, CommandList, FMenuExtensionDelegate::CreateLambda(
	[](FMenuBuilder& MenuBuilder)
	{
			//auto CommandInfo = MakeShareable(new FUICommandInfo());
			//MenuBuilder.AddMenuEntry(CommandInfo);
	}));


	TSharedRef<FExtender> ToolbarExtender(new FExtender());
	ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, CommandList, FToolBarExtensionDelegate::CreateLambda(
		[this](FToolBarBuilder& MenuBuilder)
		{
			//auto Action = MakeShared<FUIAction>();
			//TSharedPtr<FUIAction> Action = MakeShareable(new FUIAction);
			FUIAction Action;
			Action.ExecuteAction = FExecuteAction::CreateLambda([this]()
				{
                    if (!DockTab)
                    {
					    RegisterTabSpawner();
					    FGlobalTabmanager::Get()->TryInvokeTab(FTabId("LightControl"));                        
                    }
					else
					    DockTab->DrawAttention();
				});
			MenuBuilder.AddToolBarButton(Action, NAME_None, FText::FromString("Cradle Light Control"));
		}));



	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);


    LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

}

void FCradleLightControlModule::ShutdownModule()
{
	auto& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	PropertyModule.UnregisterCustomClassLayout("LightControlTool");
	PropertyModule.NotifyCustomizationModuleChanged();

	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FCradleLightControlModule::RegisterTabSpawner()
{
	auto v = FGlobalTabmanager::Get()->RegisterNomadTabSpawner("LightControl", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& Args)
		{
			DockTab = SNew(SDockTab)
				.Label(FText::FromString("Light control tab"))
				.TabRole(ETabRole::NomadTab)
				.OnTabClosed_Lambda([this](TSharedRef<SDockTab>)
					{
						FGlobalTabmanager::Get()->UnregisterNomadTabSpawner("LightControl");
						LightControl->PreDestroy();
						LightControl.Reset();
					});

			DockTab->SetContent(
				    SAssignNew(LightControl, SLightControlTool)
				    .ToolTab(DockTab)
				);

		    return DockTab.ToSharedRef();
			
		}));	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCradleLightControlModule, CradleLightControl)
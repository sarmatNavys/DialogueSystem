using UnrealBuildTool;

public class DialogueSystemEditor : ModuleRules
{
    public DialogueSystemEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore", 
                "DialogueSystemPlugin",
                "FlowEditor",
                "UnrealEd"
            }
        );
    }
}
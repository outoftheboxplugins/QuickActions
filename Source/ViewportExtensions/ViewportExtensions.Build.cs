using UnrealBuildTool;

public class ViewportExtensions : ModuleRules
{
    public ViewportExtensions(ReadOnlyTargetRules Target) : base(Target)
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
                "GeometryCollectionEditor",
                "LevelEditor",
                "Slate",
                "SlateCore", 
                "UnrealEd",
            }
        );
    }
}

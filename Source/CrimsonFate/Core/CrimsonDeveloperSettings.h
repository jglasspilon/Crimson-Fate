#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CrimsonDeveloperSettings.generated.h"

UCLASS(Config=Game, DefaultConfig)
class CRIMSONFATE_API UCrimsonDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditDefaultsOnly, Category="GridSettings")
	float GridSize = 100.f;
	
	virtual FName GetCategoryName() const override
	{
		return FApp::GetProjectName();
	}
};

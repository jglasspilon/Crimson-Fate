#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrimsonGameMode.generated.h"

UCLASS()
class CRIMSONFATE_API ACrimsonGameMode : public AGameModeBase
{
	GENERATED_BODY()
	ACrimsonGameMode();
	
protected:
	virtual void BeginPlay() override;
};

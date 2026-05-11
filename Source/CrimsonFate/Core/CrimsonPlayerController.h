#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CrimsonPlayerController.generated.h"

UCLASS()
class CRIMSONFATE_API ACrimsonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
};

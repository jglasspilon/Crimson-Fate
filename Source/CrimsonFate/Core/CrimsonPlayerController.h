#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CrimsonPlayerController.generated.h"

struct FInputActionValue;
class ACrimsonCameraPawn;
class UInputAction;

UCLASS()
class CRIMSONFATE_API ACrimsonPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Input Mapping")
	TObjectPtr<UInputAction> Input_Rotate;
	
	UPROPERTY(EditDefaultsOnly, Category="Input Mapping")
	TObjectPtr<UInputAction> Input_Move;
	
	UPROPERTY()
	TObjectPtr<ACrimsonCameraPawn> CachedCameraPawn;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	void OnRotate(const FInputActionValue& Value);
	void OnMove(const FInputActionValue& Value);
	void OnMoveEnd(const FInputActionValue& Value);
};

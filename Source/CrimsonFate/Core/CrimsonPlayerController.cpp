#include "CrimsonPlayerController.h"
#include "CrimsonCameraPawn.h"
#include "CrimsonDeveloperSettings.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void ACrimsonPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	CachedCameraPawn = Cast<ACrimsonCameraPawn>(InPawn);
}

void ACrimsonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	EnhancedInput->BindAction(Input_Rotate, ETriggerEvent::Started, this, &ThisClass::OnRotate);
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Completed, this, &ThisClass::OnMoveEnd);
}

void ACrimsonPlayerController::OnRotate(const FInputActionValue& Value)
{
	float Direction = Value.Get<float>();
	
	if (CachedCameraPawn)
	{
		CachedCameraPawn->RotateCamera(Direction);
	}
}

void ACrimsonPlayerController::OnMove(const FInputActionValue& Value)
{
	FVector Direction = Value.Get<FVector>();
	
	if (CachedCameraPawn)
	{
		CachedCameraPawn->MoveInDirection(Direction);
	}
}

void ACrimsonPlayerController::OnMoveEnd(const FInputActionValue& Value)
{
	if (CachedCameraPawn)
	{
		CachedCameraPawn->SnapToGrid();
	}
}



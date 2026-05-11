#include "CrimsonPlayerController.h"
#include "CrimsonFate/CrimsonFate.h"

void ACrimsonPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	FString Name = GetClass()->GetDisplayNameText().ToString();
	UE_LOG(LogGame, Log, TEXT("Loaded %s"), *Name);
}

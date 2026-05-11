#include "CrimsonGameMode.h"

#include "CrimsonPlayerController.h"
#include "CrimsonFate/CrimsonFate.h"

ACrimsonGameMode::ACrimsonGameMode()
{
	PlayerControllerClass = ACrimsonPlayerController::StaticClass();
}

void ACrimsonGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogGame, Log, TEXT("Started Crimson Fate Session."));
}

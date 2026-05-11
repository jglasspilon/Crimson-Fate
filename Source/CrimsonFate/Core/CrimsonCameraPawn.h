#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CrimsonCameraPawn.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class CRIMSONFATE_API ACrimsonCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ACrimsonCameraPawn();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	bool bDebugDraw;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void LookAtTarget(const FVector& TargetLocation);
};

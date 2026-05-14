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

protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USphereComponent> SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="CameraMovement")
    float CameraMoveAmount = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category="CameraMovement")
	float RotationInterpolationSpeed = 8.f;
	
	UPROPERTY(EditDefaultsOnly, Category="CameraMovement")
	float MovementInterpolationSpeed = 8.f;
	
	bool bDebugDraw;
	float ArmLength;
	float ZOffset;
	float GridSize;
	int CurrentCameraQuadrantIndex;
	FVector TargetOffset;
	FVector TargetPosition;
	
	void InterpolateRotationInTick(float DeltaTime);
	void InterpolatePositionInTick(float DeltaTime);

public:
    ACrimsonCameraPawn();
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
	
    void LookAtTarget(const FVector& TargetLocation);
    void MoveToTarget(const FVector& TargetLocation);
	void MoveInDirection(const FVector& Direction);
    void RotateCamera(int32 Direction);    
	void SnapToGrid();                                             	
};

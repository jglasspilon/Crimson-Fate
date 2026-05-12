#include "CrimsonCameraPawn.h"

#include "CrimsonDeveloperSettings.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "CrimsonFate/CrimsonGameTypes.h"
#include "GameFramework/SpringArmComponent.h"

TAutoConsoleVariable<bool> CVarCameraDebugDrawing(TEXT("game.camera.debugDraw"), false, TEXT("Enable/Disable debug draw for Camera positioning. 0 = off, 1 = on"), ECVF_Cheat);


ACrimsonCameraPawn::ACrimsonCameraPawn()
{
	const UCrimsonDeveloperSettings* DevSettings = GetDefault<UCrimsonDeveloperSettings>();
	GridSize = DevSettings->GridSize;
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SphereComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACrimsonCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	ArmLength = SpringArmComponent->TargetArmLength;
	ZOffset = SpringArmComponent->TargetOffset.Z;
	TargetOffset = SpringArmComponent->TargetOffset;
}

void ACrimsonCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bDebugDraw = CVarCameraDebugDrawing.GetValueOnGameThread();
	
	LookAtTarget(SphereComponent->GetComponentLocation());
	InterpolateRotationInTick(DeltaTime);
	InterpolatePositionInTick(DeltaTime);
	
	if (bDebugDraw)
	{
		const FVector TargetLocation = GetActorLocation();
		const FVector CamLocation = CameraComponent->GetComponentLocation(); 
		
		DrawDebugLine(GetWorld(), CamLocation, TargetLocation, FColor::Blue);
		DrawDebugBox(GetWorld(), GetActorLocation(), FVector(GridSize/2.f,GridSize/2.f,20.f), GetActorRotation().Quaternion(), FColor::White);
	}
}

void ACrimsonCameraPawn::LookAtTarget(const FVector& TargetLocation)
{
	const FVector CamLocation = CameraComponent->GetComponentLocation(); 
	const FVector Direction = (TargetLocation - CamLocation).GetSafeNormal();
	
	FRotator LookAtRotation = Direction.Rotation();
	CameraComponent->SetWorldRotation(LookAtRotation);
}

void ACrimsonCameraPawn::MoveToTarget(const FVector& TargetLocation)
{
	FVector TraceStart = FVector(TargetLocation.X, TargetLocation.Y, TargetLocation.Z + 500.f);
	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.bTraceComplex = false;
	Params.AddIgnoredActor(this);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceStart - FVector(0, 0, 2000.f), COLLISION_GROUND, Params);
	FVector FinalLocation = TargetLocation;

	if (bHit)
	{
		FinalLocation.Z = Hit.Location.Z;
	}
	
	FVector PreviousLocation = GetActorLocation();
	TargetPosition = FinalLocation;
	
	if (bDebugDraw)
	{
		DrawDebugBox(GetWorld(), PreviousLocation, FVector(GridSize/2.f,GridSize/2.f,20.f), GetActorRotation().Quaternion(), FColor::Yellow, false, 1.f);
		DrawDebugLine(GetWorld(), TraceStart,TraceStart - FVector(0,0,2000.f), FColor::Green,false,1.f);
	
		if (bHit)
			DrawDebugBox(GetWorld(), Hit.Location, FVector(20,20,20.f), GetActorRotation().Quaternion(), FColor::Red, false, 1.f);
	}
}

void ACrimsonCameraPawn::MoveInDirection(const FVector& Direction)
{
	FVector CameraForward = CameraComponent->GetForwardVector();
    FVector CameraRight = CameraComponent->GetRightVector();
	FVector CurrentLocation = GetActorLocation();
	
	float ForwardAmount = Direction.X;
    float RightAmount = Direction.Y;
	
	CameraForward.Z = 0.f;
	CameraRight.Z = 0.f;
	CameraRight = CameraRight.GetSafeNormal();
	CameraForward = CameraForward.GetSafeNormal();
	
	FVector MoveAmount = (CameraForward * ForwardAmount * CameraMoveAmount) + (CameraRight * RightAmount * CameraMoveAmount);
	MoveToTarget(CurrentLocation + MoveAmount);
}

void ACrimsonCameraPawn::RotateCamera(int32 Direction)
{
	const int NumQuadrents = 8;
	const float QuadrantSize = ArmLength;
	CurrentCameraQuadrantIndex += Direction;
	
	if (CurrentCameraQuadrantIndex >= NumQuadrents)
		CurrentCameraQuadrantIndex = 0;
	
	if (CurrentCameraQuadrantIndex < 0)
		CurrentCameraQuadrantIndex = NumQuadrents - 1;
	
	const float Theta = (CurrentCameraQuadrantIndex % NumQuadrents) * (2.f * PI / NumQuadrents);
	const float DirectionX = FMath::RoundToInt(FMath::Cos(Theta));
	const float DirectionY = FMath::RoundToInt(FMath::Sin(Theta));
	TargetOffset = FVector((-DirectionX * QuadrantSize) + QuadrantSize, DirectionY * QuadrantSize, ZOffset);
}

void ACrimsonCameraPawn::InterpolateRotationInTick(float const DeltaTime)
{
	if (SpringArmComponent->TargetOffset == TargetOffset)
		return;
	
	if (FVector::DistSquared(SpringArmComponent->TargetOffset, TargetOffset) > 1.f)
	{
		const FVector FrameTarget = FMath::VInterpTo(SpringArmComponent->TargetOffset, TargetOffset, DeltaTime, RotationInterpolationSpeed);
		SpringArmComponent->TargetOffset = FrameTarget;
	}
	else
	{
		SpringArmComponent->TargetOffset = TargetOffset;
	}
}

void ACrimsonCameraPawn::InterpolatePositionInTick(float const DeltaTime)
{
	if (GetActorLocation() == TargetPosition)
		return;
	
	if (FVector::DistSquared(GetActorLocation(), TargetPosition) > 1.f)
	{
		const FVector FrameTarget = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, MovementInterpolationSpeed);
		SetActorLocation(FrameTarget);
	}
	else
	{
		SetActorLocation(TargetPosition);
	}
}


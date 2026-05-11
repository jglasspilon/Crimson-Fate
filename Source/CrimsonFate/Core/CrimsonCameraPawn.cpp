#include "CrimsonCameraPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

TAutoConsoleVariable<bool> CVarCameraDebugDrawing(TEXT("game.camera.debugDraw"), false, TEXT("Enable/Disable debug draw for Camera positioning. 0 = off, 1 = on"), ECVF_Cheat);

ACrimsonCameraPawn::ACrimsonCameraPawn()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SphereComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ACrimsonCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACrimsonCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	LookAtTarget(SphereComponent->GetComponentLocation());
}

void ACrimsonCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bDebugDraw = CVarCameraDebugDrawing.GetValueOnGameThread();
	
	LookAtTarget(SphereComponent->GetComponentLocation());
}

void ACrimsonCameraPawn::LookAtTarget(const FVector& TargetLocation)
{
	const FVector CamLocation = CameraComponent->GetComponentLocation(); 
	const FVector Direction = (TargetLocation - CamLocation).GetSafeNormal();
	
	FRotator LookAtRotation = Direction.Rotation();
	CameraComponent->SetWorldRotation(LookAtRotation);
	
	if (bDebugDraw)
	{
		DrawDebugLine(GetWorld(), CamLocation, TargetLocation, FColor::Blue);
		DrawDebugSphere(GetWorld(), GetActorLocation(), 32, 32, FColor::Purple);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/UnrealMathUtility.h"
#include "PaperSpriteComponent.h"
#include "Tank.h"

void FTankInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.0f, 1.0f);
	MovementInput = MovementInput.GetSafeNormal();
	RawMovementInput.Set(0.0f, 0.0f);
}

void FTankInput::MoveY(float AxisValue)
{
	RawMovementInput.Y += AxisValue;
}

void FTankInput::MoveX(float AxisValue)
{
	RawMovementInput.X += AxisValue;
}



// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (RootComponent == nullptr)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TankBase"));
	}

	TankDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TankDirection"));
	TankDirection->AttachTo(RootComponent);

	TankSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TankSprite"));
	TankSprite->AttachTo(TankDirection);
	
	ChildTurret = CreateDefaultSubobject<UChildActorComponent>(TEXT("Turret"));
	ChildTurret->AttachTo(TankDirection);   // Attaching the turret to the arrow and not the sprite

	// Making a Spring Arm and editing it's properties
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->CameraLagSpeed = 2.0;
	SpringArm->bDoCollisionTest = false;
	SpringArm->AttachTo(RootComponent);
	SpringArm->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f)); // So camera looks down regardless of the root component's direction
		
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->bUsePawnControlRotation = false;
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic; 
	Camera->OrthoWidth = 2048.0f;
	Camera->AspectRatio = 4.0 / 3.0f;
	Camera->SetWorldRotation(FRotator(0.0f, 0.0f, 0.0f));
	// Socket is at the end of the spring arm, so attaching it there is important
	Camera->AttachTo(SpringArm, USpringArmComponent::SocketName); 

	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankInput.Sanitize();

	//Tank Movement
	{	// Comtaining this in scope here for future and cleanliness ;)
		FVector DesiredMovementDirection = FVector(TankInput.MovementInput.Y, TankInput.MovementInput.X, 0.0f);
		if (!DesiredMovementDirection.IsNearlyZero())
		{
			// Tank Rotation to add turning radius
			FRotator MovementAngle = DesiredMovementDirection.Rotation(); // No need to normalize this rotation, input is already sanitized
			float DeltaYaw = FMath::FindDeltaAngleDegrees(TankDirection->GetComponentRotation().Yaw, MovementAngle.Yaw);
			bool bReverse = false;
			if (DeltaYaw != 0.0f)
			{
				float AdjustedDeltaYaw = DeltaYaw;
				if (AdjustedDeltaYaw < -90.0f)
				{
					AdjustedDeltaYaw += 180.0f;
					bReverse = true;
				}

				else if (AdjustedDeltaYaw > 90.0f)
				{
					AdjustedDeltaYaw -= 180.0f;
					bReverse = true;
				}
			
				// Turn towards the desired angle, stop if reachable in one frame
				float MaxYawInFrame = YawSpeed * DeltaTime;
				if (MaxYawInFrame >= FMath::Abs(AdjustedDeltaYaw))
				{
					if (bReverse)
					{
						// Reverse movements
						FRotator FacingAngle = MovementAngle;
						FacingAngle.Yaw = MovementAngle.Yaw + 180.0f;
						TankDirection->SetWorldRotation(FacingAngle);
					}

					else
					{
						TankDirection->SetWorldRotation(MovementAngle);
					}

				}
				else
				{
					// if not reachable in one frame, rotate part way
					TankDirection->AddLocalRotation(FRotator(0.0f, FMath::Sign(AdjustedDeltaYaw) * MaxYawInFrame, 0.0f)); // Moves only upto MaxYawInFrame

				}
			
				
			}

			// Tank Movement-	
			{
				FVector MovementDirection = TankDirection->GetForwardVector() * (bReverse ? -1.0f : 1.0f);
				FVector Pos = GetActorLocation();
				Pos.Y += MovementDirection.Y * MoveSpeed * DeltaTime;
				Pos.X += MovementDirection.X * MoveSpeed * DeltaTime;
				SetActorLocation(Pos);
			}
		}
	
	}
	
}

// Key Binds
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveY", this, &ATank::MoveY);
	PlayerInputComponent->BindAxis("MoveX", this, &ATank::MoveX);
}

void ATank::MoveY(float AxisValue)
{
	TankInput.MoveY(AxisValue); //Using instance of struct for the sanitized movement data
}

void ATank::MoveX(float AxisValue)
{
	TankInput.MoveX(AxisValue); 
}
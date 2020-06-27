// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Missile.h"
#include "PaperSpriteComponent.h"
#include "Tank.h"
#include "TankStaticsFunctions.h"
#include "Turret.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TurretBase"));

	TurretDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("TurretDirection"));
	TurretDirection->AttachTo(RootComponent);
	
	TurretSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("TurretSprite"));
	TurretSprite->AttachTo(TurretDirection);

	YawSpeed = 180.0f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetParentComponent()->GetOwner());
	check(Tank);

	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(TurretDirection);
	if (Tank != nullptr)
	{
		if (APlayerController* PC = Cast<APlayerController>(Tank->GetController()))
		{
			FVector2D AimLocation;
			if (PC->GetMousePosition(AimLocation.Y, AimLocation.X))
			{
				FVector2D TurretLocation = FVector2D::ZeroVector;
				UGameplayStatics::ProjectWorldToScreen(PC, TurretDirection->GetComponentLocation(), TurretLocation);

				float DesiredYaw;
				

				if (UTankStaticsFunctions::FindLookAtAngle2D(TurretLocation, AimLocation, DesiredYaw))
				{

					FRotator CurrentRotation = TurretDirection->GetComponentRotation();
					float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentRotation.Yaw, DesiredYaw);
					float MaxDeltaYawThisFrame = YawSpeed * DeltaTime;
					if (MaxDeltaYawThisFrame >= FMath::Abs(DesiredYaw))
					{
						CurrentRotation.Yaw = DesiredYaw; //As we can reach there in this frame, just set the final value to it
						
					}
					
					else
					{
						CurrentRotation.Yaw	+= FMath::Sign(DeltaYaw)* MaxDeltaYawThisFrame;
						
					}
					TurretDirection->SetWorldRotation(CurrentRotation);
					
				}
			}
			
		}
		const FTankInput& CurrentInput = Tank->GetCurrentInput();
		if (CurrentInput.bFire1 && Projectile)
		{
			if (UWorld* World = GetWorld())
			{
				
				if (AActor* NewProjectile = World->SpawnActor(Projectile))
				{
					FVector Loc = TurretSprite->GetSocketLocation("Muzzle");
					FRotator Rot = TurretDirection->GetComponentRotation();
					NewProjectile->SetActorLocation(Loc);
					NewProjectile->SetActorRotation(Rot);


				}
			}
		}
	}
}
					

					



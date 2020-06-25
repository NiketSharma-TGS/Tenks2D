// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
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
	TurretSprite->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	check(TurretDirection);
	if (ATank* Tank = Cast<ATank>(ParentComponentActor.Get()))
	{
		if (APlayerController* PC = Cast<APlayerController>(Tank->GetController()))
		{
			FVector2D AimLocation;
			if (PC->GetMousePosition(AimLocation.Y, AimLocation.X))
			{
				FVector2D TurretLocation = FVector2D::ZeroVector;
				UGameplayStatics::ProjectWorldToScreen(PC, TurretDirection->GetComponentLocation(), TurretLocation);

				float DesiredYaw;
				FRotator CurrentRotation = TurretDirection->GetComponentRotation();

				if (UTankStaticsFunctions::FindLookAtAngle2D(TurretLocation, AimLocation, DesiredYaw))
				{

					CurrentRotation.Yaw = DesiredYaw;
					TurretDirection->SetWorldRotation(CurrentRotation);

				}
			}
		}
	}
}


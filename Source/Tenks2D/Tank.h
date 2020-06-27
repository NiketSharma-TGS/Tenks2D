// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


/*USTRUCT() 
struct AttachmentRules
{
	GENERATED_BODY()

public:

	bool bWeldSimulatedBodies = true;

	EAttachmentRule LocationRule;
	EAttachmentRule RotationtionRule;
	EAttachmentRule ScaleRule;

};*/


USTRUCT(BlueprintType) // Holds all the inputs and cleans them
struct FTankInput
{
	GENERATED_BODY()

public:
// Sanitizing movement speed

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TankInput)
	
	FVector2D MovementInput;

	// These can't be UFUNCTIONS because USTRUCT is not an UOBJECT
	void Sanitize();
	void MoveY(float AxisValue);
	void MoveX(float AxisValue);

private:
	// Internal Raw data hidden from game code
	FVector2D RawMovementInput;
};


UCLASS()
class TENKS2D_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	// Kry Binds
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);



private:
	
	// Debug arrow
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* TankDirection;

	// Tank body Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TankSprite;

	// Turret Actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildTurret;

	// In-game camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;
	

	// Max speed(degrees per seconds) of rotating
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tank, meta = (ClampMin = "0.0"), meta = (AllowPrivateAccess = "true"))
	float YawSpeed = 180;

	// Movement Speed(units/seconds)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tank, meta = (ClampMin = "0.0"), meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100;

	
protected:
	
	// Input Struct
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TankInput, meta = (AllowPrivateAccess = "true"))
	FTankInput TankInput;
	
	
};
 
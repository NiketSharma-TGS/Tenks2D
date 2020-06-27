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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TankInput)
	bool bFire1; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TankInput)
	bool bFire2; 


	// These can't be UFUNCTIONS because USTRUCT is not an UOBJECT
	void Sanitize();
	void MoveY(float AxisValue);
	void MoveX(float AxisValue);
	void Fire1(bool bPressed);
	void Fire2(bool bPressed);

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

	// Key Binds
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = Tank)

	const FTankInput& GetCurrentInput() { return TankInput; }

private:
	
	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void Fire1Pressed();
	void Fire1Released();
	void Fire2Pressed();
	void Fire2Released();


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
 
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	
	//Debug arrow
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* TankDirection;

	//Tank body Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tank, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TankSprite;

	
};

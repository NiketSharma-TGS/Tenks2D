// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class ATank;  //Man do I love me some forward declarations

UCLASS()
class TENKS2D_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Max. turning rate deg/sec
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	float YawSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	ATank* Tank;

private:

	//Debug arrow
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Turret, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* TurretDirection;

	//Tank body Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Turret, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* TurretSprite;

};

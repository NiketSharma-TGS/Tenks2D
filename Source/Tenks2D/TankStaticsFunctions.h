// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TankStaticsFunctions.generated.h"

/**
 * 
 */
UCLASS()
class TENKS2D_API UTankStaticsFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:		
	
		// To get the angle between two 2D points
		UFUNCTION(BlueprintPure, Category = MathRotator, meta = (Keywords = "rotation rotate"))
		static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle);


};

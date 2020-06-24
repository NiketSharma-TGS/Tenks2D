// Fill out your copyright notice in the Description page of Project Settings.


#include "TankStaticsFunctions.h"



bool UTankStaticsFunctions::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	FVector2D Normal = (Target - Start).GetSafeNormal();

	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}

	return false;
}
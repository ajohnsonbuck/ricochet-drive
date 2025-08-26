// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RicochetDriveMathFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RICOCHETDRIVE_API URicochetDriveMathFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable,Category="CustomMath")
    static float CompressedSigmoidalDiff(float x, float a, float x0);

	UFUNCTION(BlueprintCallable, Category = "CustomMath")
	static float StretchedHalfSineDiff(float x, float a, float n);

	UFUNCTION(BlueprintCallable, Category = "CustomMath")
	static float PiecewiseLinearDiff(float x, float x_start, float x_end);
};
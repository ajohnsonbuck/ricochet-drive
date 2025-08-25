// Fill out your copyright notice in the Description page of Project Settings.

#include "RicochetDriveMathFunctionLibrary.h"
#include "Math/UnrealMathUtility.h" // for FMath::Exp

float URicochetDriveMathFunctionLibrary::CompressedSigmoidalDiff(float x, float a, float x0) 
{

	float b = FMath::Exp(-a * (x - x0));

	return a * b / FMath::Pow(1.0 + b, 2.0);

}

float URicochetDriveMathFunctionLibrary::StretchedHalfSine(float x, float a, float n)
{
	float pi = 3.141592654;

	float b = (pi / a) * (FMath::Pow(x, n)) - pi / 2;

	float c = 0.5 * pi * n * FMath::Pow(x, n - 1);

	return c * FMath::Cos(b);

}

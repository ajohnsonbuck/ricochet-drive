// Fill out your copyright notice in the Description page of Project Settings.

#include "RicochetDriveMathFunctionLibrary.h"
#include "Math/UnrealMathUtility.h" // for FMath::Exp, etc.

//SHIP MOVEMENT FUNCTIONS, USED IN BP_SHIP_MOVEMENT CLASS
float URicochetDriveMathFunctionLibrary::CompressedSigmoidalDiff(float x, float a, float x0)
{  // df/dx, where f(x) = 1/(1 + exp(-a*(x - x0))
   // Sharply defined sigmoidal function, good for ship turning in middle of level
   // Larger a gives sharper sigmoidal; x0 (on [0, 1]) gives normalized midpoint of transition

	float b = FMath::Exp(-a * (x - x0));

	return a * b / FMath::Pow(1.0 + b, 2.0);

}

float URicochetDriveMathFunctionLibrary::StretchedHalfSine(float x, float a, float n)
{	// df/dx, where f(x) = 0.5*a*(sin(pi/a*x^n - pi/2) + 1)
	// First half of a sine period stretched to fill ([0,1],[0,1])
	// Larger a gives more stretched sine; larger n gives sharper acceleration/deceleration curve

	float pi = 3.141592654;

	float b = (pi / a) * (FMath::Pow(x, n)) - pi / 2;

	float c = 0.5 * pi * n * FMath::Pow(x, n - 1);

	return c * FMath::Cos(b);

}

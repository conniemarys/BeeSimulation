// Fill out your copyright notice in the Description page of Project Settings.


#include "Enum_CellWallSides.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class Enum_CellWallSides
{
	None = 1,
	NorthEast = 2,
	East = 4,
	SouthEast = 8,
	SouthWest = 16, 
	West = 32, 
	NorthWest = 64

};
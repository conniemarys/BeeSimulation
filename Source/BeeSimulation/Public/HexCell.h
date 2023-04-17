// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexGridManager.h"
#include "HexCell.generated.h"

/**
 * 
 */
UCLASS()
class BEESIMULATION_API AHexCell : public AHexGridManager
{
	GENERATED_BODY()
	


public:

	AHexCell();
	AHexCell(int x, int y, int32 wallSides);

	int X;
	int Y;
	int32 WallSides;
};

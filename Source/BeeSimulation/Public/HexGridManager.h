// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameManager.h"
#include "HexGridManager.generated.h"

/**
 * 
 */
UCLASS()
class BEESIMULATION_API AHexGridManager : public AGameManager
{
	GENERATED_BODY()

protected:

	AHexGridManager();
	
public:

	int Width;
	int Height;

	TArray<TArray<UObject*>> HexCellGrid;

	AHexGridManager(int width, int height);

	void TestPopulateArray();
};

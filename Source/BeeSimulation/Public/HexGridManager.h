// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array2DSimulater.h"
#include "GameManager.h"
#include "HexGridManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEESIMULATION_API AHexGridManager : public AGameModeBase
{
	GENERATED_BODY()

protected:

	AHexGridManager();
	
public:

	AHexGridManager(int width, int height);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Width = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Height = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FArray2DSimulator> HexCellArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;

	UFUNCTION(BlueprintCallable)
	void PopulateArray(UStaticMesh* defaultStaticMesh);
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EWallSidesBits : uint8
{
	EWB_None = 0x00,
	EWB_East = 0x01,
	EWB_SouthEast = 0x02,
	EWB_SouthWest = 0x04,
	EWB_West = 0x08,
	EWB_NorthWest = 0x16,
	EWB_NorthEast = 0x32
};
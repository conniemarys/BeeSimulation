// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexCell.h"
#include "Engine/UserDefinedStruct.h"
#include "Array2DSimulater.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FArray2DSimulator
{
	//BEESIMULATION_API
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FHexCell> Ar;

	FHexCell operator[](int32 i)
	{
		return Ar[i];
	}

	void Add(FHexCell hexCell)
	{
		Ar.Add(hexCell);
	}
	
};

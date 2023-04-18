// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexCell.h"
#include "Engine/UserDefinedStruct.h"
#include "Cell2DArraySimulator.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FHexCell2DArraySimulator
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

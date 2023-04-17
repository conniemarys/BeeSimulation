// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexCell.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHexCell
{
	GENERATED_BODY()
	


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WallSides;

};

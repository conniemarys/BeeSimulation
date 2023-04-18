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
	int InstanceInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> WallInstances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "EWallSidesBits"))
	int32 eWallSidesBits;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMesh *StaticMesh;


};

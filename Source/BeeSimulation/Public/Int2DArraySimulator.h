// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedStruct.h"
#include "Int2DArraySimulator.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FInt2DArraySimulator
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> Ar;

	int operator[](int32 i)
	{
		return Ar[i];
	}

	void Add(int i)
	{
		Ar.Add(i);
	}

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class BEESIMULATION_API AGameManager : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Meta = (Bitmask, BitmaskEnum = "EWallSidesBits"))
	//UPROPERTY(BlueprintReadWrite, Meta = (Bitmask))
	int32 eWallSidesBits;

};

//UseEnumValuesAsMaskValuesInEditor = "true"
UENUM(Meta = (Bitflags))
enum class EWallSidesBits
{
	EWB_East = 0x01,
	EWB_SouthEast = 0x02,
	EWB_SouthWest = 0x04,
	EWB_West = 0x08,
	EWB_NorthWest = 0x16,
	EWB_NorthEast = 0x32
};

ENUM_CLASS_FLAGS(EWallSidesBits);
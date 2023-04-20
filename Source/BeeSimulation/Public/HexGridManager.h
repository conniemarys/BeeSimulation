// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Cell2DArraySimulator.h"
#include "Int2DArraySimulator.h"
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
	TArray<FHexCell2DArraySimulator> HexCellArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FInt2DArraySimulator> InstancesArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius;
	
	UFUNCTION(BlueprintCallable)
	void PopulateArray(UStaticMesh* defaultStaticMesh);

	UFUNCTION(BlueprintCallable)
	bool HasFlag(UPARAM(meta = (Bitmask, BitmaskEnum = EWallSidesBits)) int32 flagToCheck, int32 valueToCheck);

	UFUNCTION(BlueprintCallable)
	void SetFlagOnHexCell(UPARAM(meta = (Bitmask, BitmaskEnum = EWallSidesBits)) int32 flagToSet, FHexCell hexCell);

	UFUNCTION(BlueprintCallable)
	void SetFlag(UPARAM(meta = (Bitmask, BitmaskEnum = EWallSidesBits)) int32 flagToSet, int32 valueToAddTo);

	UFUNCTION(BlueprintCallable)
	void RemoveFlagOnHexCell(UPARAM(meta = (Bitmask, BitmaskEnum = EWallSidesBits)) int32 flagToRemove, FHexCell hexCell);

	UFUNCTION(BlueprintCallable)
	void RemoveFlag(UPARAM(meta = (Bitmask, BitmaskEnum = EWallSidesBits)) int32 flagToRemove, int32 valueToRemoveFrom);

};

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EWallSidesBits : uint8
{
	EWB_None = 0x00 UMETA(Hidden),
	EWB_East = 1 << 0, //0x01,
	EWB_SouthEast = 1 << 1, //0x02,
	EWB_SouthWest = 1 << 2, //0x04,
	EWB_West = 1 << 3, //0x08,
	EWB_NorthWest = 1 << 4,//0x16,
	EWB_NorthEast = 1 << 5//0x32
};
ENUM_CLASS_FLAGS(EWallSidesBits)
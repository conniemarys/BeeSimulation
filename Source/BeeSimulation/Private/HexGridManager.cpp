// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"

AHexGridManager::AHexGridManager()
{
}

AHexGridManager::AHexGridManager(int width, int height)
{
	Width = width;
	Height = height;
}

UFUNCTION(BlueprintCallable)
void AHexGridManager::PopulateArray(UStaticMesh* defaultMesh)
{
	Radius = defaultMesh->GetBoundingBox().Max.X;

	for (int x = 0; x < Width; x++)
	{
		HexCellArray.Add(FHexCell2DArraySimulator());

		for (int y = 0; y < Height; y++)
		{
			FHexCell cellToAdd = FHexCell();
			cellToAdd.StaticMesh = defaultMesh;
			cellToAdd.X = x;
			cellToAdd.Y = y;
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_East;

			HexCellArray[x].Add(cellToAdd);
		}
	}
}

UFUNCTION(BlueprintCallable)
bool AHexGridManager::HasFlag(int32 flagToCheck, int32 valueToCheck)
{
	return (valueToCheck & flagToCheck) == flagToCheck;

}

bool AHexGridManager::ScriptHasFlag(int32 flagToCheck, int32 valueToCheck)
{
	return (valueToCheck & flagToCheck) == flagToCheck;
}

UFUNCTION(BlueprintCallable)
void AHexGridManager::SetFlagOnHexCell(int32 flagToSet, FHexCell hexCell)
{
	hexCell.eWallSidesBits |= flagToSet;
}

UFUNCTION(BlueprintCallable)
void AHexGridManager::SetFlag(int32 flagToSet, int32 valueToAddTo)
{
	valueToAddTo |= flagToSet;
}

UFUNCTION(BlueprintCallable)
void AHexGridManager::RemoveFlagOnHexCell(int32 flagToRemove, FHexCell hexCell)
{
	hexCell.eWallSidesBits &= flagToRemove;
}

UFUNCTION(BlueprintCallable)
void AHexGridManager::RemoveFlag(int32 flagToRemove, int32 valueToRemoveFrom)
{
	valueToRemoveFrom &= flagToRemove;
}


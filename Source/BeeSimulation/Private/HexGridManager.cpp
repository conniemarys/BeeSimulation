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
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_West;
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_NorthWest;
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_NorthEast;
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_SouthWest;
			cellToAdd.eWallSidesBits |= (int)EWallSidesBits::EWB_SouthEast;

			HexCellArray[x].Add(cellToAdd);
		}
	}
}

UFUNCTION(BlueprintCallable)
bool AHexGridManager::HasFlag(int32 flagToCheck, int32 valueToCheck)
{
	return (valueToCheck & flagToCheck) == flagToCheck;

}

UFUNCTION(BlueprintCallable)
TArray<FTransform> AHexGridManager::GetWallTransforms(int32 valueToCheck, FTransform cellTransform)
{
	TArray<FTransform> wallLocations = {};
	FVector cellLocation = cellTransform.GetLocation();
	FQuat cellRotation = cellTransform.GetRotation();
	FVector cellScale = cellTransform.GetScale3D();
	

	if ((valueToCheck & (int)EWallSidesBits::EWB_East) == (int)EWallSidesBits::EWB_East)
	{
		FVector wallLocation = cellLocation + FVector(-60, 0, 0);
		wallLocations.Add(FTransform(cellRotation, wallLocation, cellScale));
	};
	if ((valueToCheck & (int)EWallSidesBits::EWB_SouthEast) == (int)EWallSidesBits::EWB_SouthEast)
	{
		FVector wallLocation = cellLocation + FVector(-30, -52, 0);
		FQuat wallRotation = cellRotation + FQuat(0, 0, 60, 1);
		wallLocations.Add(FTransform(wallRotation, wallLocation, cellScale));
	};
	if ((valueToCheck & (int)EWallSidesBits::EWB_SouthWest) == (int)EWallSidesBits::EWB_SouthWest)
	{
		FVector wallLocation = cellLocation + FVector(30, -52, 0);
		FQuat wallRotation = cellRotation + FQuat(0, 0, 120, 1);
		wallLocations.Add(FTransform(wallRotation, wallLocation, cellScale));
	};
	if ((valueToCheck & (int)EWallSidesBits::EWB_West) == (int)EWallSidesBits::EWB_West)
	{
		FVector wallLocation = cellLocation + FVector(60, 0, 0);
		FQuat wallRotation = cellRotation + FQuat(0, 0, 180, 1);
		wallLocations.Add(FTransform(wallRotation, wallLocation, cellScale));
	};
	if ((valueToCheck & (int)EWallSidesBits::EWB_NorthWest) == (int)EWallSidesBits::EWB_NorthWest)
	{
		FVector wallLocation = cellLocation + FVector(30, 52, 0);
		FQuat wallRotation = cellRotation + FQuat(0, 0, -120, 1);
		wallLocations.Add(FTransform(wallRotation, wallLocation, cellScale));
	};
	if ((valueToCheck & (int)EWallSidesBits::EWB_NorthEast) == (int)EWallSidesBits::EWB_NorthEast)
	{
		FVector wallLocation = cellLocation + FVector(-30, 52, 0);
		FQuat wallRotation = FQuat(0, 0, -60, 1);
		wallLocations.Add(FTransform(wallRotation, wallLocation, cellScale));
	};

	return wallLocations;
}
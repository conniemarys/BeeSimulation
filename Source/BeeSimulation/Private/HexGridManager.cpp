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
			HexCellArray[x].Add(cellToAdd);
		}
	}
}

TArray<FTransform> AHexGridManager::GetWallLocations(FHexCell hexCell)
{
	TArray<FTransform> wallLocations = {};

	int32 eWallSidesBits = hexCell.eWallSidesBits;


	return wallLocations;
}
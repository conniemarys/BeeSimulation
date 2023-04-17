// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"

AHexGridManager::AHexGridManager() 
{
}

AHexGridManager::AHexGridManager(int width, int height)
{
	Width = width;
	Height = height;
	PopulateArray();
}

void AHexGridManager::PopulateArray()
{
	for (int x = 0; x < Width; x++)
	{
		HexCellArray.Add(FArray2DSimulator());

		for (int y = 0; y < Height; y++)
		{
			HexCellArray[x].Add(FHexCell());
		}
	}
}
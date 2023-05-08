// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cell2DArraySimulator.h"
#include "HexCell.h"
#include "AStarPathfinder.h"	
#include "Components/ActorComponent.h"
#include "MazeGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEESIMULATION_API UMazeGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable)
	static TArray<FHexCell2DArraySimulator> GenerateMaze(TArray<FHexCell2DArraySimulator> grid);

private:


	static int32 GetOppositeWall(int32 wallSide);

	static TArray<FHexCell> GetUnvisitedNeighbours(FHexCell hexCell, TArray<FHexCell> visitedCells, TArray<FHexCell2DArraySimulator> grid);
	static int FindSharedWall(FHexCell hexCell, FHexCell neighbour);

		
};

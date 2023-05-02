// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HexCell.h"
#include "Cell2DArraySimulator.h"
#include "HexGridManager.h"
#include "Components/ActorComponent.h"
#include "AStarPathfinder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEESIMULATION_API UAStarPathfinder : public UActorComponent
{
	GENERATED_BODY()


public:

	// Sets default values for this component's properties
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Find Path", CompactNodeTitle = "Path Find", Keywords = "Path Find A Star"), Category = Game)
		TArray<FHexCell> PathFind(TArray<FHexCell2DArraySimulator> inputGrid, FHexCell startNode, FHexCell endNode);

private:
	TArray<FHexCell2DArraySimulator> SetOriginalCosts(TArray <FHexCell2DArraySimulator> grid);
	int CalculateFCost(FHexCell hexCell);
	int CalculateHCost(FHexCell node, FHexCell endNode);
	int FindLowestFCost(TArray<FHexCell> openList);
	bool ListContains(TArray<FHexCell> list, FHexCell node);
	int ListFind(TArray<FHexCell> list, FHexCell node);
	TArray<FHexCell> TracePath(FHexCell hexCell, TArray<FHexCell> closedList, TArray<FHexCell> path);
	TArray<FHexCell> FindNeighbours(TArray<FHexCell2DArraySimulator> grid, FHexCell hexCell);
	TArray<FHexCell> RecursiveCall(TArray<FHexCell> openList, TArray<FHexCell> closedList, TArray<FHexCell2DArraySimulator> grid, FHexCell endNode);

};

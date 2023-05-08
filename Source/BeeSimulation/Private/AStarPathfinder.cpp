// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPathfinder.h"
#include "HexCell.h"
#include "Cell2DArraySimulator.h"
#include "HexGridManager.h"


// Sets default values for this component's properties
UFUNCTION(BlueprintCallable)
TArray<FHexCell> UAStarPathfinder::PathFind(TArray<FHexCell2DArraySimulator> inputGrid, FHexCell startNode, FHexCell endNode)
{
	TArray<FHexCell2DArraySimulator> grid = SetOriginalCosts(inputGrid);
	startNode.GCost = 0;
	startNode.HCost = CalculateHCost(startNode, endNode);
	startNode.FCost = CalculateFCost(startNode);
	startNode.parentX = -1;
	startNode.parentY = -1;
	grid[startNode.X][startNode.Y] = startNode;
	TArray<FHexCell> openList = { startNode };
	TArray<FHexCell> closedList;

	return RecursiveCall(openList, closedList, grid, endNode);

}

TArray<FHexCell> UAStarPathfinder::RecursiveCall(TArray<FHexCell> openList, TArray<FHexCell> closedList, TArray<FHexCell2DArraySimulator> grid, FHexCell endNode)
{
	if (openList.Num() == 0)
	{
		TArray<FHexCell> path = {};
		return path;
	}

	int LowestFCostIndex = FindLowestFCost(openList);
	FHexCell currentNode = openList[LowestFCostIndex];
	openList.RemoveAt(LowestFCostIndex);
	closedList.Add(currentNode);

	TArray<FHexCell> neighbours = FindNeighbours(grid, currentNode);

	for (int i = 0; i < neighbours.Num(); i++)
	{
		if(!ListContains(closedList, neighbours[i]))
		{
			FHexCell neighbourNode = neighbours[i];

			if (neighbourNode.X == endNode.X && neighbourNode.Y == endNode.Y)
			{
				TArray<FHexCell> path = { neighbourNode };
				return TracePath(currentNode, closedList, path);
			}
			else
			{
				neighbourNode.GCost = currentNode.GCost + 1;
				neighbourNode.HCost = CalculateHCost(neighbourNode, endNode);
				neighbourNode.FCost = CalculateFCost(neighbourNode);
				neighbourNode.parentX = currentNode.X;
				neighbourNode.parentY = currentNode.Y;

				if (ListContains(openList, neighbourNode))
				{
					if (openList[ListFind(openList, neighbourNode)].GCost > neighbourNode.GCost)
					{
						openList.RemoveAt(ListFind(openList, neighbourNode));
						openList.Add(neighbourNode);
					}
				}
				else
				{
					openList.Add(neighbourNode);
				}

			}

		}

		
	}
	
	return RecursiveCall(openList, closedList, grid, endNode);
	

}

TArray<FHexCell> UAStarPathfinder::TracePath(FHexCell hexCell, TArray<FHexCell> closedList, TArray<FHexCell> path)
{
	path.Add(hexCell);
	if (hexCell.parentX == -1 && hexCell.parentY == -1)
	{
		return path;
	}
	else
	{
		for (int i = 0; i < closedList.Num(); i++)
		{
			if (hexCell.parentX == closedList[i].X && hexCell.parentY == closedList[i].Y)
			{
				FHexCell parentCell = closedList[i];
				return TracePath(parentCell, closedList, path);
			}
		}
		
	}

	return path;

}

int UAStarPathfinder::ListFind(TArray<FHexCell> list, FHexCell node)
{
	for (int i = 0; i < list.Num(); i++)
	{
		if (list[i].X == node.X && list[i].Y == node.Y)
		{
			return i;
		}
	}

	return -1;
}

bool UAStarPathfinder::ListContains(TArray<FHexCell>list, FHexCell node)
{
	for (int i = 0; i < list.Num(); i++)
	{
		if (list[i].X == node.X && list[i].Y == node.Y)
		{
			return true;
		}
	}

	return false;
}

int UAStarPathfinder::CalculateHCost(FHexCell node, FHexCell endNode)
{
	return abs(node.X - endNode.X) + abs(node.Y - endNode.Y);
}

TArray<FHexCell2DArraySimulator> UAStarPathfinder::SetOriginalCosts(TArray<FHexCell2DArraySimulator> grid)
{
	TArray<FHexCell2DArraySimulator> outerGrid;

	for (int x = 0; x < grid.Num(); x++)
	{
		FHexCell2DArraySimulator innerGrid;

		for (int y = 0; y < grid[0].Num(); y++)
		{
			FHexCell hexCell = grid[x][y];
			hexCell.HCost = 0;
			hexCell.GCost = std::numeric_limits<float>::infinity();
			hexCell.FCost = CalculateFCost(hexCell);
			hexCell.parentX = -1;
			hexCell.parentY = -1;
			innerGrid.Add(hexCell);
		}

		outerGrid.Add(innerGrid);
	}

	return outerGrid;
}

int UAStarPathfinder::CalculateFCost(FHexCell hexCell)
{
	return hexCell.HCost + hexCell.GCost;
	
}

int UAStarPathfinder::FindLowestFCost(TArray<FHexCell> openList)
{
	int lowestFCostCellIndex = 0;

	for (int i = 0; i < openList.Num(); i++)
	{
		if (openList[lowestFCostCellIndex].FCost > openList[i].FCost)
		{
			lowestFCostCellIndex = i;
		}
	}

	return lowestFCostCellIndex;
}


TArray<FHexCell> UAStarPathfinder::FindNeighbours(TArray<FHexCell2DArraySimulator> grid, FHexCell hexCell)
{
	int xLocation = hexCell.X;
	int yLocation = hexCell.Y;
	TArray<FHexCell> neighbours;

	if (xLocation % 2 == 0)
	{
		//NorthEast
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_NorthEast) != (int)EWallSidesBits::EWB_NorthEast && xLocation != grid.Num() - 1 && yLocation != grid[0].Num() - 1)
		{
			neighbours.Add(grid[xLocation + 1][yLocation + 1]);
		}
		//SouthEast
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_SouthEast) != (int)EWallSidesBits::EWB_SouthEast && xLocation != grid.Num() - 1)
		{
			neighbours.Add(grid[xLocation + 1][yLocation]);
		}
		//SouthWest
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_SouthWest) != (int)EWallSidesBits::EWB_SouthWest && xLocation != 0)
		{
			neighbours.Add(grid[xLocation - 1][yLocation]);
		}
		//NorthWest
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_NorthWest) != (int)EWallSidesBits::EWB_NorthWest && yLocation != grid[0].Num() - 1 && xLocation != 0)
		{
			neighbours.Add(grid[xLocation - 1][yLocation + 1]);
		}
	}
	else
	{
		//NorthEast
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_NorthEast) != (int)EWallSidesBits::EWB_NorthEast && xLocation != grid.Num() - 1)
		{
			neighbours.Add(grid[xLocation + 1][yLocation]);
		}
		//SouthEast
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_SouthEast) != (int)EWallSidesBits::EWB_SouthEast && yLocation != 0 && xLocation != grid.Num() - 1)
		{
			neighbours.Add(grid[xLocation + 1][yLocation - 1]);
		}
		//SouthWest
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_SouthWest) != (int)EWallSidesBits::EWB_SouthWest && yLocation != 0 && xLocation != 0)
		{
			neighbours.Add(grid[xLocation - 1][yLocation - 1]);
		}
		//NorthWest
		if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_NorthWest) != (int)EWallSidesBits::EWB_NorthWest && xLocation != 0)
		{
			neighbours.Add(grid[xLocation - 1][yLocation]);
		}
	}

	//South
	if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_South) != (int)EWallSidesBits::EWB_South && yLocation != 0)
	{
		neighbours.Add(grid[xLocation][yLocation - 1]);
	}
	//North
	if ((hexCell.eWallSidesBits & (int)EWallSidesBits::EWB_North) != (int)EWallSidesBits::EWB_North && yLocation != grid[0].Num() - 1)
	{
		neighbours.Add(grid[xLocation][yLocation + 1]);
	}

	return neighbours;
}





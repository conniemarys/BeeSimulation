// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"

UFUNCTION(BlueprintCallable)
TArray<FHexCell2DArraySimulator> UMazeGenerator::GenerateMaze(TArray<FHexCell2DArraySimulator> grid)
{
	TArray<FHexCell> visitedCells;
	TArray<FHexCell> positionStack;

	TArray<FHexCell2DArraySimulator> returnGrid = grid;

	FHexCell position = returnGrid[FMath::RandRange(0, returnGrid.Num() - 1)][FMath::RandRange(0, returnGrid[0].Num() - 1)];
	positionStack.Add(position);
	visitedCells.Add(position);

	while (positionStack.Num() > 0)
	{
		FHexCell currentCell = positionStack.Last();

		positionStack.RemoveAt(positionStack.Num() - 1);

		TArray<FHexCell> neighbours = GetUnvisitedNeighbours(currentCell, visitedCells, returnGrid);

		if (neighbours.Num() > 0)
		{
			int randIndex = FMath::RandRange(0, neighbours.Num() - 1);
			FHexCell randomNeighbour = neighbours[randIndex];

			int sharedWall = FindSharedWall(currentCell, randomNeighbour);

			currentCell.eWallSidesBits = currentCell.eWallSidesBits & ~sharedWall;
			randomNeighbour.eWallSidesBits = randomNeighbour.eWallSidesBits & ~GetOppositeWall(sharedWall);

			returnGrid[currentCell.X].SetCellAtIndex(currentCell, currentCell.Y);
			returnGrid[randomNeighbour.X].SetCellAtIndex(randomNeighbour, randomNeighbour.Y);

			positionStack.Add(currentCell);
		
			visitedCells.Add(randomNeighbour);
			positionStack.Add(randomNeighbour);

		}

	}

	return returnGrid;
}

int UMazeGenerator::FindSharedWall(FHexCell hexCell, FHexCell neighbour)
{
	if (hexCell.X % 2 == 0)
	{
		if (hexCell.X + 1 == neighbour.X && hexCell.Y + 1 == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_NorthEast;
		}
		else if (hexCell.X + 1 == neighbour.X && hexCell.Y == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_SouthEast;
		}
		else if (hexCell.X - 1 == neighbour.X && hexCell.Y + 1 == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_NorthWest;
		}
		else if (hexCell.X - 1 == neighbour.X && hexCell.Y == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_SouthWest;
		}
	}

	else
	{
		if (hexCell.X + 1 == neighbour.X && hexCell.Y - 1 == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_SouthEast;
		}
		else if (hexCell.X + 1 == neighbour.X && hexCell.Y == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_NorthEast;
		}
		else if (hexCell.X - 1 == neighbour.X && hexCell.Y - 1 == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_SouthWest;
		}
		else if (hexCell.X - 1 == neighbour.X && hexCell.Y == neighbour.Y)
		{
			return (int)EWallSidesBits::EWB_NorthWest;
		}
	}

	if (hexCell.X == neighbour.X && hexCell.Y + 1 == neighbour.Y)
	{
		return (int)EWallSidesBits::EWB_North;
	}

	else if (hexCell.X == neighbour.X && hexCell.Y - 1 == neighbour.Y)
	{
		return (int)EWallSidesBits::EWB_South;
	}

	else
	{
		return -1;
	}

}

int UMazeGenerator::GetOppositeWall(int wallSide)
{
	switch (wallSide)
	{
		case (int)EWallSidesBits::EWB_North: return (int)EWallSidesBits::EWB_South;
		case (int)EWallSidesBits::EWB_NorthWest: return (int)EWallSidesBits::EWB_SouthEast;
		case (int)EWallSidesBits::EWB_NorthEast: return (int)EWallSidesBits::EWB_SouthWest;
		case (int)EWallSidesBits::EWB_South: return (int)EWallSidesBits::EWB_North;
		case (int)EWallSidesBits::EWB_SouthEast: return (int)EWallSidesBits::EWB_NorthWest;
		case (int)EWallSidesBits::EWB_SouthWest: return (int)EWallSidesBits::EWB_NorthEast;
		default: return -1;
	}
}

TArray<FHexCell> UMazeGenerator::GetUnvisitedNeighbours(FHexCell hexCell, TArray<FHexCell> visitedCells, TArray<FHexCell2DArraySimulator> grid)
{
	TArray<FHexCell> neighbours;

	if (hexCell.X % 2 == 0)
	{
		if (hexCell.X < grid.Num() - 1)
		{
			if (hexCell.Y < grid[0].Num() - 1 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X + 1][hexCell.Y + 1]))
			{
				//NorthEast
				neighbours.Add(grid[hexCell.X + 1][hexCell.Y + 1]);
			}

			if (!UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X + 1][hexCell.Y]))
			{
				//SouthEast
				neighbours.Add(grid[hexCell.X + 1][hexCell.Y]);
			}
		}

		if (hexCell.X > 0)
		{
			if (hexCell.Y < grid[0].Num() - 1 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X - 1][hexCell.Y + 1]))
			{
				//NorthWest
				neighbours.Add(grid[hexCell.X - 1][hexCell.Y + 1]);
			}

			//SouthWest
			if (!UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X - 1][hexCell.Y]))
			{
				neighbours.Add(grid[hexCell.X - 1][hexCell.Y]);
			}
		}
	}

	if (hexCell.X % 2 != 0)
	{
		if (hexCell.X < grid.Num() - 1)
		{
			if (hexCell.Y > 0 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X + 1][hexCell.Y - 1]))
			{
				//SouthEast
				neighbours.Add(grid[hexCell.X + 1][hexCell.Y - 1]);
			}

			if (!UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X + 1][hexCell.Y]))
			{
				//NorthEast
				neighbours.Add(grid[hexCell.X + 1][hexCell.Y]);
			}
		}

		if (hexCell.X > 0)
		{
			if (hexCell.Y > 0 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X - 1][hexCell.Y - 1]))
			{
				//SouthWest
				neighbours.Add(grid[hexCell.X - 1][hexCell.Y - 1]);
			}

			if (!UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X - 1][hexCell.Y]))
			{
				//NorthWest
				neighbours.Add(grid[hexCell.X - 1][hexCell.Y]);
			}
		}
	}

	if (hexCell.Y > 0 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X][hexCell.Y - 1]))
	{
		//South
		neighbours.Add(grid[hexCell.X][hexCell.Y - 1]);
	}
	if (hexCell.Y < grid[0].Num() - 1 && !UAStarPathfinder::ListContains(visitedCells, grid[hexCell.X][hexCell.Y + 1]))
	{
		//North
		neighbours.Add(grid[hexCell.X][hexCell.Y + 1]);
	}

	return neighbours;
}




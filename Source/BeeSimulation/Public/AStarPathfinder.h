// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AStarPathfinder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEESIMULATION_API UAStarPathfinder : public UActorComponent
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "A Star Pathfinder", CompactNodeTitle = "AStarPathfinder", Keywords = "Path Find A Star"), Category = Game)
		static TArray<UStruct*> PathFind(TArray<UStruct*> cellArray, int height, int width);

public:	
	// Sets default values for this component's properties
	UAStarPathfinder();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameController.generated.h"


/**
 * 
 */
class ATarget;
UCLASS()
class SPACETEST01_API AGameController : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGameController();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<float> WaveDificulty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TArray<int> WaveSpawnFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		int CurrentWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My variables")
		TSubclassOf<ATarget> Target_BP;

private:
	int LeftToSpawn;
	float Clock;
	bool GameWon;
	void ChangeWave(int wave);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ATarget;

UCLASS()
class SPACETEST01_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int AmoutOfEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int WaveCount; // controlls how many waves to win the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int enemiesDefeated;
	UFUNCTION()
		void SpawnEnemy();
	UFUNCTION()
		void DefeatedEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MinY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MaxY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My variables")
		TSubclassOf<ATarget> Target_BP;

public:
	float Clock;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "My variables")
	bool hasWon;
};

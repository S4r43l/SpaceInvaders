// Fill out your copyright notice in the Description page of Project Settings.


#include "GameController.h"
#include "Target.h"

AGameController::AGameController() {
	
	PrimaryActorTick.bCanEverTick = true;
	
	WaveSize.Add(10);
	WaveSize.Add(10);
	WaveSize.Add(20);

	WaveDificulty.Add(0.f);
	WaveDificulty.Add(1);
	WaveDificulty.Add(2);
	
	WaveSpawnFrequency.Add(2);
	WaveSpawnFrequency.Add(1);
	WaveSpawnFrequency.Add(0.5);

	MaxX = 2000;
	MaxY = 2000;

	MinX = 400;
	MaxY = -400;
	
}

void AGameController::BeginPlay()
{
	Super::BeginPlay();

	CurrentWave = 1;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Clock += DeltaTime;
	if (Clock > WaveSpawnFrequency[CurrentWave - 1] && !GameWon) {
		Clock = 0.f;
		FVector location = FVector(FMath::FRandRange(MinX, MaxX), FMath::FRandRange(MinY, MaxY), 80);
		//spawn the 
		AActor* Actor = GetWorld()->SpawnActor<AActor>(Target_BP, location, FRotator::ZeroRotator);
		ATarget* Target = Cast<ATarget>(Actor);
		//Target->MovementSpeed *= WaveDificulty[CurrentWave - 1];
		LeftToSpawn--;
		if (LeftToSpawn <= 0) {
			ChangeWave(CurrentWave + 1);
		}
	}


}

void AGameController::ChangeWave(int wave)
{
	if (WaveSize.Num() < wave) {

		GameWon = true;
		return;
	}

	CurrentWave  = wave;
	LeftToSpawn = WaveSize[CurrentWave - 1];
}

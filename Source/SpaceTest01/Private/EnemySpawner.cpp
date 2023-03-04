// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Target.h"


// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	WaveCount = 0;
	AmoutOfEnemies = 3;
	enemiesDefeated = 0;

	MaxX = 200;
	MaxY = 70;

	MinX = 120;
	MaxY = -70;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Clock += DeltaTime;
	if (Clock > 7) {
		SpawnEnemy();
		Clock = 0.f;
		
	}
}

void AEnemySpawner::SpawnEnemy()
{
	
	if (hasWon)
		return;
	if (WaveCount < 3) {
		for (int i = 0; i < AmoutOfEnemies; i++) {
			//instatiate an enemy
			// 
			AmoutOfEnemies = FMath::FRandRange(2, 15);
			FVector location = FVector(FMath::FRandRange(MinX, MaxX), FMath::FRandRange(MinY, MaxY), 80);
			AActor* Actor = GetWorld()->SpawnActor<AActor>(Target_BP, location, FRotator::ZeroRotator);
			ATarget* Target = Cast<ATarget>(Actor);
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Spawned the enemy"));
		}
	}
	WaveCount++;
	if (WaveCount > 3) {
		hasWon = true;
		UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/Levels/Victory.Victory'"));
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("YOU WIN!"));
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

void AEnemySpawner::DefeatedEnemy()
{
	enemiesDefeated++;
	if (enemiesDefeated >= 3 && WaveCount < 3) {
		WaveCount++;
		enemiesDefeated = 0;
		
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("DEAD"));
		//spawn a new wave of enemies
	}
	else if(WaveCount >= 3) {
		// win the game, should add a debug message for this
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, TEXT("Wave count over 3 :D"));
	}
}


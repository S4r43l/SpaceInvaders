// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"
#include "EnemySpawner.h"
#include "MyPlayer.h"

// Sets default values
class AEnemySpawner;
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(50, 50, 50));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 40.f));

	MovementSpeed = 350;
	RotationSpeed = 1.f;
	XKillPosition = -2000.0f;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	RotationSpeed = FMath::RandRange(0.5f, 1.5f);
	MovementSpeed += FMath::RandRange(0, 250);
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();

	NewLocation += FVector(-1, 0, 0) * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	SetActorRotation(GetActorRotation() + FRotator(0, RotationSpeed, 0));


	//murder
	if (GetActorLocation().X < XKillPosition) {
		DestoryTarget();
	}
}

void ATarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AMyPlayer>()) {
		Cast<AMyPlayer>(OtherActor)->HitByTarget();
		
		DestoryTarget();
	}
	
	
}

void ATarget::DestoryTarget()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	
	//AEnemySpawner* Spawner;

	this->Destroy();

}
void ATarget::DefeatTheTarget() {

	

}


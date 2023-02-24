// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Target.h"
#include "EnemySpawner.h"

// Sets default values
class AEnemySpawner;
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	Collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(Collider);
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	MovementSpeed = 2000.0f;
	Timelived = 0.f;
	lifeSpan = 10.f;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;

	SetActorLocation(NewLocation);
	Timelived += DeltaTime;
	if (Timelived > lifeSpan) {
		DestroyBullet();
	}
};

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<ATarget>()) {
		
		
		Cast<ATarget>(OtherActor)->DestoryTarget();
		
		
		//Cast<AEnemySpawner>(OtherActor)->DefeatedEnemy();
		DestroyBullet();
		//to do Destory target DONE :D :D :D
	}
}

void ABullet::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"


class UBoxComponent;

UCLASS()
class SPACETEST01_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//componentes


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Collider{nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;
	
	
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void DestoryTarget();
	UFUNCTION()
		void DefeatTheTarget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float XKillPosition;

};

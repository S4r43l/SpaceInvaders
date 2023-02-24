// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "MyPlayer.generated.h"


class USpringArmComponent;
//class UStaticMesh;
class UCameraComponent;
class ABullet;
class UEnhancedInputComponent;
UCLASS()
class SPACETEST01_API AMyPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputMappingContext* IMCinput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCameraComponent* CameraComponent;

	//blueprint ref
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My variables")
		TSubclassOf<ABullet> Bullet_BP;

	//variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="My Variables")
		int Ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="My Variables")
		int MaxAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int lives;
	void HitByTarget();
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputMappingContext* IMC;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_Forward;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_Right;
	
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_Shoot;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_Reload;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_ResetGame;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_MouseX;
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = InputSystem)
		class UInputAction* IA_MouseY;

	
	UFUNCTION(BlueprintCallable)
		void MouseX(const FInputActionValue& val);
	UFUNCTION(BlueprintCallable)
		void MouseY(const FInputActionValue& val);

	UFUNCTION(BlueprintCallable)
		void Forward(const FInputActionValue& val);
	UFUNCTION(BlueprintCallable)
		void Right(const FInputActionValue& val);
	
	//UFUNCTION(BlueprintCallable)
		//void ResetGame(const FInputActionValue& val);
	UFUNCTION(BlueprintCallable)
		void Reload(const FInputActionValue& val);
	UFUNCTION(BlueprintCallable)
		void Shoot(const FInputActionValue& val);
	UFUNCTION(BlueprintCallable)
		void Reset(const FInputActionValue& val);

private:
	float XInput;
	float YInput;

	float Yaw;
	float Pitch;

private:
	/*void Forward(float input);
	void Right(float input);

	void Shoot();
	void Reload();*/




};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "Bullet.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "EnemySpawner.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values

AMyPlayer::AMyPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetRelativeLocation(FVector(0, 0, 0));
	StaticMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;


	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	Ammo = 100;
	MaxAmmo = 100;
	lives = 10;
	MovementSpeed = 1000;
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController) {
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (subsystem) {
			subsystem->AddMappingContext(IMCinput, 0);

		}
	}
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	FVector ForwardVector = FVector(XInput, YInput, 0.f);
	ForwardVector.Normalize();

	FVector NewLocation = GetActorLocation() + (ForwardVector * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation);

	// to stop crashing
	AddControllerPitchInput(Pitch);
	AddControllerYawInput(Yaw);
	if ((Controller != nullptr) && (XInput != 0.0f)) 
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;
		// get the local forward vector normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
		SetActorLocation(GetActorLocation() + (Direction * XInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
	if ((Controller != nullptr) && (YInput != 0.0f))
	{
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.f;
		Rotation.Roll = 0.f;
		// get the local forward vector normalized
		FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
		SetActorLocation(GetActorLocation() + (Direction * YInput * MovementSpeed * DeltaTime));

		SetActorRotation(Rotation);
	}
}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*PlayerInputComponent->BindAxis("Forward", this, &AMyPlayer::Forward);
	PlayerInputComponent->BindAxis("Right", this, &AMyPlayer::Right);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPlayer::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AMyPlayer::Reload);*/

	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhanceInputCom->BindAction(IA_Forward, ETriggerEvent::Triggered, this, &AMyPlayer::Forward);
		EnhanceInputCom->BindAction(IA_Right, ETriggerEvent::Triggered, this, &AMyPlayer::Right);

		EnhanceInputCom->BindAction(IA_Forward, ETriggerEvent::Completed, this, &AMyPlayer::Forward);
		EnhanceInputCom->BindAction(IA_Right, ETriggerEvent::Completed, this, &AMyPlayer::Right);
		
		//EnhanceInputCom->BindAction(IA_Left, ETriggerEvent::Completed, this, &AMyPlayer::Left);
		EnhanceInputCom->BindAction(IA_MouseX, ETriggerEvent::Completed, this, &AMyPlayer::MouseX);
		EnhanceInputCom->BindAction(IA_MouseX, ETriggerEvent::Triggered, this, &AMyPlayer::MouseX);
		EnhanceInputCom->BindAction(IA_MouseX, ETriggerEvent::Started, this, &AMyPlayer::MouseX);

		EnhanceInputCom->BindAction(IA_MouseY, ETriggerEvent::Completed, this, &AMyPlayer::MouseY);
		EnhanceInputCom->BindAction(IA_MouseY, ETriggerEvent::Triggered, this, &AMyPlayer::MouseY);
		EnhanceInputCom->BindAction(IA_Shoot, ETriggerEvent::Started, this, &AMyPlayer::Shoot);
		EnhanceInputCom->BindAction(IA_Shoot, ETriggerEvent::Triggered, this, &AMyPlayer::Shoot);
		EnhanceInputCom->BindAction(IA_Reload, ETriggerEvent::Started, this, &AMyPlayer::Reload);
		EnhanceInputCom->BindAction(IA_ResetGame, ETriggerEvent::Started, this, &AMyPlayer::Reset);
	
	}



}

void AMyPlayer::HitByTarget()
{
	lives--;
	if (lives <= 0) {
		

		//add Ui to this
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("YOU DEAD AHAHAHH AHAHXDXDXDXD"));
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("YOU DEAD AHAHAHH AHAHXDXDXDXD"));
		//game over
	}
}





void AMyPlayer::MouseX(const FInputActionValue& val)
{
	Yaw = val.Get<float>();
	AddControllerYawInput(Yaw);
}
void AMyPlayer::Reset(const FInputActionValue& val)
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMyPlayer::MouseY(const FInputActionValue& val)
{
	Pitch = val.Get<float>();
	AddControllerPitchInput(Pitch);
}

void AMyPlayer::Forward(const FInputActionValue& val)
{
	XInput = val.Get<float>();
}

void AMyPlayer::Right(const FInputActionValue& val)
{
	YInput = val.Get<float>();
}



void AMyPlayer::Reload(const FInputActionValue& val)
{
	Ammo = MaxAmmo;
}

void AMyPlayer::Shoot(const FInputActionValue& val)
{
	if (Ammo > 0) {
		
	


		if ((Controller != nullptr) && (YInput != 0.0f))
		{
			FRotator Rotation = Controller->GetControlRotation();
			Rotation.Pitch = 0.f;
			Rotation.Roll = 0.f;
			// get the local forward vector normalized
			FVector Direction = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);
			//SetActorLocation(GetActorLocation() + (Direction * YInput * MovementSpeed * DeltaTime));

			//SetActorRotation(Rotation);
			GetWorld()->SpawnActor<AActor>(Bullet_BP,
				GetActorLocation() + (Direction * 50.0f), Rotation);
			Ammo--;

		}
	}
	
}

//void AMyPlayer::Forward(float input)
//{
//	//XInput = input;
//}
//
//void AMyPlayer::Right(float input)
//{
//	//YInput = input;


//void AMyPlayer::Shoot()
//{
//	/*if (Ammo > 0) {
//		Ammo--;
//		GetWorld()->SpawnActor<AActor>(Bullet_BP, 
//			GetActorLocation() + FVector(30.f,0.f,0.f), GetActorRotation());
//
//	}*/
//}
//
//void AMyPlayer::Reload()
//{
//	//Ammo = MaxAmmo;
//}


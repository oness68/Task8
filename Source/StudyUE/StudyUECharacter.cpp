// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUECharacter.h"
#include "Camera/CameraComponent.h"
#include "StudyUECharacterController.h"
#include "EnhancedInputComponent.h"
#include "StudyUEGameInstance.h"
#include"GameFramework/SpringArmComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
// Sets default values
AStudyUECharacter::AStudyUECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true; //컨트롤러 회전 적용


	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	NormalSpeed = 600.0f;
	SprintSpeedMulitplier = 1.3f;
	SprintSpeed = NormalSpeed * SprintSpeedMulitplier;

	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	MaxHealth = 100.0f;
	Health = MaxHealth;



}

// Called when the game starts or when spawned
void AStudyUECharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStudyUECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStudyUECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AStudyUECharacterController* PlayerController = Cast<AStudyUECharacterController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AStudyUECharacter::Move);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &AStudyUECharacter::StartJump);
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Completed, this, &AStudyUECharacter::StopJump);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AStudyUECharacter::Look);
			}

			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &AStudyUECharacter::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &AStudyUECharacter::StopSprint);

			}
			if (PlayerController->PauseAction)
			{
				EnhancedInput->BindAction(PlayerController->PauseAction, ETriggerEvent::Started, this, &AStudyUECharacter::PauseGames);

			}

		}
	}
}

float AStudyUECharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health decreased to : %f"), Health);
	HPUpdate();

	if (Health <= 0.0f)
	{
		OnDeath();
	}

	return 0.0f;
}

float AStudyUECharacter::GetHealth() const
{
	return Health;
}

void AStudyUECharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, 100.0f);
	UE_LOG(LogTemp, Warning, TEXT("Health increased to : %f"), Health);

}

void AStudyUECharacter::OnDeath()
{
}


void AStudyUECharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}
}

void AStudyUECharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void AStudyUECharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void AStudyUECharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AStudyUECharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AStudyUECharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;
	}
}

void AStudyUECharacter::PauseGames(const FInputActionValue& value)
{

	AStudyUECharacterController* PlayerController = Cast<AStudyUECharacterController>(GetController());

	if (PlayerController)
	{


		PlayerController->SetPause(true);
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetUI(UIState::PauseMenu);


	}


}






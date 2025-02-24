// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUECharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "StudyUEGameInstance.h"
#include "StudyUEGameState.h"

AStudyUECharacterController::AStudyUECharacterController() :
	InputMappingContext(nullptr), 
	MoveAction(nullptr),
	JumpAction(nullptr),
	SprintAction(nullptr),
	LookAction(nullptr),
	HUDWidgetInstance(nullptr),
	ManuWidgetInstance(nullptr),
	PauseWidgetInstance(nullptr)
{
	CurrentUIState = UIState::NullValue;

}



void AStudyUECharacterController::BeginPlay()
{
	Super::BeginPlay();
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext,0);
			}
		}
	}

	UGameInstance* GameInstance = GetGameInstance();

	if (GameInstance)
	{
		UStudyUEGameInstance* STGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
		if (STGameInstance)
		{
			CurrentUIState = STGameInstance->GetGameUIState();
		}
	}
	SetUI(CurrentUIState);

}

UUserWidget* AStudyUECharacterController::GetHUDWidget() const
{

	return HUDWidgetInstance;
}

void AStudyUECharacterController::SetUI(UIState state)
{


	if (ManuWidgetInstance)
	{
		ManuWidgetInstance->RemoveFromParent();
		UE_LOG(LogTemp, Warning, TEXT("RomoveMenu"));
		ManuWidgetInstance = nullptr;
	}
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (PauseWidgetInstance)
	{
		PauseWidgetInstance->RemoveFromParent();
		PauseWidgetInstance = nullptr;
	}
	switch (state)
	{
	case UIState::MainMenu:
	{

		if (ManuWidgetClass)
		{
			ManuWidgetInstance = CreateWidget<UUserWidget>(this, ManuWidgetClass);
			if (ManuWidgetInstance)
			{
				ManuWidgetInstance->AddToViewport();
			}

		}
		break;
	}
	case UIState::InGame:
	{

		if (HUDWidgetClass)
		{
			HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
			if (HUDWidgetInstance)
			{
				HUDWidgetInstance->AddToViewport();
			}
		}

		AStudyUEGameState* StudyUEGameState = GetWorld() ? GetWorld()->GetGameState<AStudyUEGameState>() : nullptr;

		if (StudyUEGameState)
		{
			StudyUEGameState->UpdateHUD();
		}
		
		break;
	}

	case UIState::PauseMenu:
	{

		if (PauseWidgetClass)
		{
			PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);
			if (PauseWidgetInstance)
			{
				PauseWidgetInstance->AddToViewport();
			}
		}
		break;
	}
	default:
		break;
	}
}

void AStudyUECharacterController::RunGame()
{
	AStudyUEGameState* StudyUEGameState = GetWorld() ? GetWorld()->GetGameState<AStudyUEGameState>() : nullptr;
	StudyUEGameState->PlayGames();

}









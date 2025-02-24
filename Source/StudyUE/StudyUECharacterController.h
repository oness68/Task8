// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StudyUEGameState.h"

#include "StudyUECharacterController.generated.h"


class UInputMappingContext;
class UInputAction;




/**
 * 
 */
UCLASS()
class STUDYUE_API AStudyUECharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AStudyUECharacterController();
	virtual void BeginPlay();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* PauseAction;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> ManuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	UUserWidget* ManuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	UUserWidget* PauseWidgetInstance;


	UIState CurrentUIState;



	UFUNCTION(BlueprintCallable, Category = "HUD")
	UUserWidget* GetHUDWidget() const;
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetUI(UIState state);

	UFUNCTION(BlueprintCallable)
	void RunGame();

	

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StudyUEGameInstance.generated.h"

/**
 * 
 * 
 */

UENUM(BlueprintType)
enum class UIState :uint8
{
	NullValue UMETA(DisplayName = "Null"),
	MainMenu UMETA(DisplayName = "MenuUI"),
	InGame UMETA(DisplayName = "InGameUI"),
	PauseMenu UMETA(DisplayName = "PauseUI")


};


UCLASS()
class STUDYUE_API UStudyUEGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UStudyUEGameInstance();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "GameData")
	int32 TotalScore;

	UPROPERTY(BlueprintReadWrite, Category = "GameData")
	int32 CurrnetLevelIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	UIState GameUIState;

	UFUNCTION(BlueprintPure)
	UIState GetGameUIState()const;

	void SetGameUIState(UIState State);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void ReStartGames();
	

};

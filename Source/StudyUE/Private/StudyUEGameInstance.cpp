// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUEGameInstance.h"

UStudyUEGameInstance::UStudyUEGameInstance()
{
	TotalScore = 0;
	CurrnetLevelIndex = 0;
	GameUIState = UIState::MainMenu;
}

UIState UStudyUEGameInstance::GetGameUIState() const
{
	return GameUIState;
}

void UStudyUEGameInstance::SetGameUIState(UIState State)
{
	GameUIState = State;
}

void UStudyUEGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score  : %d"), TotalScore);
}

void UStudyUEGameInstance::ReStartGames()
{
	TotalScore = 0;
	CurrnetLevelIndex = 0;
	GameUIState = UIState::MainMenu;
}


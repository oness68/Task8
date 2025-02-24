// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUEGameMode.h"
#include"StudyUE/StudyUECharacterController.h"
#include "StudyUE/StudyUECharacter.h"
#include "StudyUEGameState.h"

AStudyUEGameMode::AStudyUEGameMode()
{
	DefaultPawnClass = AStudyUECharacter::StaticClass();
	PlayerControllerClass = AStudyUECharacterController::StaticClass();
	GameStateClass = AStudyUEGameState::StaticClass();
}

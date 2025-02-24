// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUEGameModeBase.h"
#include"StudyUECharacterController.h"
#include "StudyUECharacter.h"
#include "StudyUEGameState.h"

AStudyUEGameModeBase::AStudyUEGameModeBase()
{
	DefaultPawnClass = AStudyUECharacter::StaticClass();
	PlayerControllerClass = AStudyUECharacterController::StaticClass();
	GameStateClass = AStudyUEGameState::StaticClass();
}

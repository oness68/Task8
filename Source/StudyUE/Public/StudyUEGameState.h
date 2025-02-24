// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "StudyUEGameState.generated.h"

/**
 * 
 */



UCLASS()
class STUDYUE_API AStudyUEGameState : public AGameState
{
	GENERATED_BODY()
	

public:
	AStudyUEGameState();

	virtual void BeginPlay() override;



	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Score")
	int32 Score;

	

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectdCoinCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	float WaveDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrnetLevelIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 MaxWaves;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentWave;


	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TArray<FName> LevelMapsNames;

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameOver();

	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnCoinCollected();

	
	UFUNCTION(BlueprintCallable)
	void PlayGames();


	void StartLevel();
	void StartWave();
	void OnWaveTimeUp();
	void EndLevel();
	void EndWave();

	UFUNCTION(BlueprintCallable)
	void UpdateHUD();


};

// Fill out your copyright notice in the Description page of Project Settings.


#include "StudyUEGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "StudyUE/CoinItem.h"
#include "StudyUEGameInstance.h"
#include "StudyUE/StudyUECharacterController.h"
#include "Components/TextBlock.h"
#include "StudyUEGameInstance.h"
#include "Blueprint/UserWidget.h"

AStudyUEGameState::AStudyUEGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectdCoinCount = 0;
	WaveDuration = 60.0f;
	CurrnetLevelIndex = 0;
	MaxLevels = 3;
	CurrentWave = 1;
	MaxWaves = 3;

}

void AStudyUEGameState::BeginPlay()
{
	Super::BeginPlay();
	//if (UGameInstance* GameInstance = GetGameInstance())
	//{
	//	UStudyUEGameInstance* STGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
	//	

	//}

}

int32 AStudyUEGameState::GetScore() const
{
	return Score;
}

void AStudyUEGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UStudyUEGameInstance* STGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
		if (STGameInstance)
		{
			STGameInstance->AddToScore(Amount);
		}
	}

	Score += Amount;

	UE_LOG(LogTemp, Warning, TEXT("Score : %d"), Score);
}

void AStudyUEGameState::OnGameOver()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectdCoinCount = 0;
	WaveDuration = 60.0f;
	CurrnetLevelIndex = 0;
	MaxLevels = 3;
	CurrentWave = 1;
	MaxWaves = 3;


	UGameplayStatics::OpenLevel(GetWorld(), LevelMapsNames[CurrnetLevelIndex]);


}

void AStudyUEGameState::OnCoinCollected()
{
	CollectdCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected : %d / %d"), CollectdCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectdCoinCount >= SpawnedCoinCount)
	{
		EndWave();
	}

}



void AStudyUEGameState::PlayGames()
{


	StartLevel();
	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AStudyUEGameState::UpdateHUD,
		0.1f,
		true
	);


}

void AStudyUEGameState::StartLevel()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UStudyUEGameInstance* STGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
		if (STGameInstance)
		{
			CurrnetLevelIndex = STGameInstance->CurrnetLevelIndex;
			
		}
	}
	StartWave();

	
	 
}

void AStudyUEGameState::StartWave()
{

	SpawnedCoinCount = 0;
	CollectdCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 10 * CurrentWave * (CurrnetLevelIndex);

	for (size_t i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolumes = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolumes)
			{
				AActor* SpawnedActor = SpawnVolumes->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}



	UpdateHUD();

	GetWorldTimerManager().SetTimer( //웨이브 시간제한
		LevelTimerHandle,
		this,
		&AStudyUEGameState::OnWaveTimeUp,
		WaveDuration,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("Wave %d Start!, Spawned %d coin"),
		CurrentWave,
		SpawnedCoinCount)


}

void AStudyUEGameState::OnWaveTimeUp()
{
	EndWave();
}

void AStudyUEGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UStudyUEGameInstance* STGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
		if (STGameInstance)
		{
			AddScore(Score);
			CurrnetLevelIndex++;
			STGameInstance->CurrnetLevelIndex = CurrnetLevelIndex;
		}
	}



	if (CurrnetLevelIndex > MaxLevels-1)
	{
		OnGameOver();
		return;
	}
	if (LevelMapsNames.IsValidIndex(CurrnetLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapsNames[CurrnetLevelIndex]);
	}
	else
	{
	
		OnGameOver();
	}
}

void AStudyUEGameState::EndWave()
{
	TArray<AActor*> ActorItem;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseItem::StaticClass(), ActorItem);

	if (!ActorItem.IsEmpty())
	{
		for (auto it : ActorItem)
		{
			it->Destroy();
		}

	}


	CurrentWave++;

	if (CurrentWave > MaxWaves)
	{
		EndLevel();
	}
	else
	{
		StartWave();
	}

}

void AStudyUEGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		AStudyUECharacterController* StudyPlayerController = Cast<AStudyUECharacterController>(PlayerController);
		if (StudyPlayerController)
		{
			if (UUserWidget* HUDWidget = StudyPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{

					if (UGameInstance* GameInstance = GetGameInstance())
					{
						UStudyUEGameInstance* StudyGameInstance = Cast<UStudyUEGameInstance>(GameInstance);
						if (StudyGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), StudyGameInstance->TotalScore)));

						}
					}

				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrnetLevelIndex)));
				}

				if (UTextBlock* WaveText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					WaveText->SetText(FText::FromString(FString::Printf(TEXT("Wave : %d"), CurrentWave)));
				}
			}
		}
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HealingItem.h"
#include "StudyUECharacter.h"


AHealingItem::AHealingItem()
{
	HealAmount = 20.0f;
	ItemType = "Healing";

}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AStudyUECharacter* PlayerCharacter = Cast<AStudyUECharacter>(Activator))
		{
			PlayerCharacter->AddHealth(HealAmount);
		}


		DestroyItem();
	}
}

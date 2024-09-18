// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameplayGameState.h"

AGameplayGameState::AGameplayGameState()
{

}

/*
void AGameplayGameState::LoadGameplayStreamLevel(FVector spawnCoords)
{
	UE_LOG(LogTemp, Warning, TEXT("Starting level streaming on client!"));

	FName levelName = "L_Gameplay_Stream";
	UGameplayStatics::LoadStreamLevel(GetWorld(), levelName, false, false, FLatentActionInfo());
	//ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), levelName);
	//StreamingLevel->LevelTransform.SetTranslation(FVector(-24916.0, 0, 0));
	//StreamingLevel->SetShouldBeVisible(true);
}
*/
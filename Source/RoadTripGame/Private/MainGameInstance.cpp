// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

UMainGameInstance::UMainGameInstance()
{

}

void UMainGameInstance::Init()
{
	if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();

		if (SessionInterface.IsValid())
		{
			// Bind delegates here
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMainGameInstance::OnCreateSessionComplete);
		}
	}
}

void UMainGameInstance::OnCreateSessionComplete(FName ServerName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("Create session completed: %d"), Succeeded);

	if (Succeeded)
	{
		GetWorld()->ServerTravel("/Game/RoadTripGame/Levels/L_GameplayPersistent?listen");
	}
}

void UMainGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating session from Game Instance"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.NumPublicConnections = 5;
	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);
}

void UMainGameInstance::JoinSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining session from Game Instance"));

}
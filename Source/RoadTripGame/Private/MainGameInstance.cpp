// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Online/OnlineSessionNames.h"

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
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMainGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UMainGameInstance::OnJoinSessionComplete);
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

void UMainGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("Find sessions completed: %d"), Succeeded);

	if (Succeeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		if(SearchResults.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Found session, joining"));
			SessionInterface->JoinSession(0, "My Session", SearchResults[0]);
		}
	}
}

void UMainGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("Join session complete"));

	if (APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
		{
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void UMainGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating session from Game Instance"));

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.NumPublicConnections = 5;

	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL")
	{
		SessionSettings.bIsLANMatch = false;
	}
	else
	{
		SessionSettings.bIsLANMatch = true;
	}

	SessionInterface->CreateSession(0, FName("My Session"), SessionSettings);
}

void UMainGameInstance::JoinSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining session from Game Instance"));

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = false;
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	if (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL")
	{
		SessionSearch->bIsLanQuery = false;
	}
	else
	{
		SessionSearch->bIsLanQuery = true;
	}
	
	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}
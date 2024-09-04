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
		}
	}
}

void UMainGameInstance::CreateSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating session from Game Instance"));
}

void UMainGameInstance::JoinSession()
{
	UE_LOG(LogTemp, Warning, TEXT("Joining session from Game Instance"));

}
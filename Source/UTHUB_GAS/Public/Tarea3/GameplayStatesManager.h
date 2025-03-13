#pragma once

#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

class FGameplayStatesManager : public FNoncopyable
{
	static FGameplayStatesManager* Singleton;
	
public:
	static FGameplayStatesManager& Get()
	{
		if(!Singleton)
			Singleton = new FGameplayStatesManager();

		return *Singleton;
	}

	void InitGameplayTags()
	{
		Tag_InteractEnabled = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("GameStates.CanInteract"));
		Tag_StatusHealthy = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Gameplay.Status.Healthy"));
		Tag_StatusInfected = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Gameplay.Status.Infected"));
		Tag_StatusContagious = UGameplayTagsManager::Get().AddNativeGameplayTag(TEXT("Gameplay.Status.Contagious"));
	}

public:
	FGameplayTag Tag_InteractEnabled;
	FGameplayTag Tag_StatusHealthy;
	FGameplayTag Tag_StatusInfected;
	FGameplayTag Tag_StatusContagious;
};

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "InputAbilityMapping.generated.h"


UCLASS()
class UTHUB_GAS_API UInputAbilityMapping : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category=Mapping)
	TMap<UInputAction*, TSubclassOf<UGameplayAbility>> Mapping;
};

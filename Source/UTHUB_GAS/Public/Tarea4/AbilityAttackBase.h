#pragma once

#include "CoreMinimal.h"
#include "AbilityBase_Busy.h"
#include "AbilityAttackBase.generated.h"

UCLASS()
class UTHUB_GAS_API UAbilityAttackBase : public UAbilityBase_Busy
{
	GENERATED_BODY()

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
};

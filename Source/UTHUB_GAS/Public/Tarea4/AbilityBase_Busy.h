#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityBase_Busy.generated.h"

UCLASS()
class UTHUB_GAS_API UAbilityBase_Busy : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UAbilityBase_Busy();
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnAnimationFinished();
	
	UPROPERTY(EditAnywhere, Category=Attack, meta=(AllowPrivateAccess=true))
	UAnimMontage* MontageToPlay;
};

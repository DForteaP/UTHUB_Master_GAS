#include "Tarea4/AbilityBase_Busy.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Tarea4/DamageCollisionEvaluator.h"

UAbilityBase_Busy::UAbilityBase_Busy()
{
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(TEXT("Character.IsBusy")));
}

void UAbilityBase_Busy::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                        const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	const AActor* Avatar = ActorInfo->AvatarActor.Get();
	check(Avatar);

	if(UDamageCollisionEvaluator* CollisionEvaluator = Avatar->FindComponentByClass<UDamageCollisionEvaluator>())
	{
		CollisionEvaluator->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ApplyDamageEffects);
	}
	
	UAbilityTask_PlayMontageAndWait* PlayMontageAndWait =
		UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, MontageToPlay);

	PlayMontageAndWait->OnCompleted.AddDynamic(this, &ThisClass::OnAnimationFinished);
	
	PlayMontageAndWait->Activate();
}

void UAbilityBase_Busy::ApplyDamageEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void UAbilityBase_Busy::OnAnimationFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

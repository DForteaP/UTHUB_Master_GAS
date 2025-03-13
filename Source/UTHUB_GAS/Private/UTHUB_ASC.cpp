#include "UTHUB_GAS/Public/UTHUB_ASC.h"

#include "Tarea3/CoreAttributeSet.h"
#include "Tarea3/Components/GASDataComponent.h"

UUTHUB_ASC::UUTHUB_ASC()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo(GetOwner(), GetOwner());
}

void UUTHUB_ASC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);
	InitializeAttributesFromEffects();
}

void UUTHUB_ASC::AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& InGameplayAbilityClass)
{
	FGameplayAbilitySpec Spec(InGameplayAbilityClass, 1, 0);
	GiveAbility(Spec);
}

void UUTHUB_ASC::InitializeAttributes(const AActor* InOwnerActor) const
{
	if(UCoreAttributeSet* CoreAttributes = GetAttributeSetFromOwner<UCoreAttributeSet>())
	{
		if(const UGASDataComponent* DataComponent = InOwnerActor->FindComponentByClass<UGASDataComponent>())
		{
			if(DataComponent->DT_CoreStats)
			{
				auto InitializeAttribute = [this, CoreAttributes](const FName& RowName, const FGameplayCoreAttribute& Row)
				{
					float NewValue = Row.AttributeBaseValue;
					Row.Attribute.SetNumericValueChecked(NewValue, CoreAttributes);
				};
		
				DataComponent->DT_CoreStats->ForeachRow<FGameplayCoreAttribute>(TEXT(""), InitializeAttribute);
			}		
		}
	}
}

FActiveGameplayEffectHandle UUTHUB_ASC::ApplyGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass)
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle Spec = MakeOutgoingSpec(EffectClass, 1, EffectContext);
			
	return ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void UUTHUB_ASC::ModifyAttributeGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass, const float InPeriod, float InDamage)
{
	FGameplayEffectContextHandle EffectContext = MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle Spec = MakeOutgoingSpec(EffectClass, 1, EffectContext);
	Spec.Data.Get()->Period = InPeriod;
	Spec.Data.Get()->Period = InPeriod;
	
	ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
}

void UUTHUB_ASC::InitializeAttributesFromEffects()
{
	UGASDataComponent* DataComponent = GetOwner()->FindComponentByClass<UGASDataComponent>();

	if(DataComponent)
	{
		for(const auto& EffectClass : DataComponent->AttributeInitializers)
		{
			ApplyGameplayEffect(EffectClass);
		}
	}
	
}
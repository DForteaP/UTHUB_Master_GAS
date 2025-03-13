#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitySystemComponent.h"
#include "UTHUB_ASC.generated.h"


UINTERFACE(NotBlueprintable)
class UGameplayTagCustomInterface : public UGameplayTagAssetInterface
{
	GENERATED_BODY()
};

class IGameplayTagCustomInterface : public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	virtual void AddTags(const FGameplayTag& InTag) = 0;
	
	UFUNCTION(BlueprintCallable, Category = "GameplayTags")
	virtual void RemoveTags(FGameplayTag& InTag) = 0;
	
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UTHUB_GAS_API UUTHUB_ASC : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UUTHUB_ASC();

protected:
	virtual void BeginPlay() override;
	void InitializeAttributes(const AActor* InOwnerActor) const;
	void InitializeAttributesFromEffects();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	
	void AddAbilityFromClass(const TSubclassOf<UGameplayAbility>& InGameplayAbilityClass);
	
	UFUNCTION(BlueprintCallable)
	FActiveGameplayEffectHandle ApplyGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass);
	
	UFUNCTION(BlueprintCallable)
	void ModifyAttributeGameplayEffect(const TSubclassOf<UGameplayEffect>& EffectClass, float InPeriod, float InDamage);
	
private:	

	template<typename AttrSetType>
	AttrSetType* GetAttributeSetFromOwner() const;
};


template <typename AttrSetType>
AttrSetType* UUTHUB_ASC::GetAttributeSetFromOwner() const
{
	if(!GetOwner()) return nullptr;
	
	TArray<UObject*> OutSubobjects;
	GetOwner()->GetDefaultSubobjects(OutSubobjects);

	UObject** AttributeSet = OutSubobjects.FindByPredicate([](const UObject* Obj)
	{
		return Obj->IsA(AttrSetType::StaticClass());
	});

	if(!AttributeSet) return nullptr;

	return Cast<AttrSetType>(*AttributeSet);
}
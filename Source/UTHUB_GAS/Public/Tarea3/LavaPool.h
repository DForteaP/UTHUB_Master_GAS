#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "UTHUB_ASC.h"
#include "GameFramework/Actor.h"
#include "LavaPool.generated.h"

class UCoreAttributeSet;

UCLASS()
class UTHUB_GAS_API ALavaPool : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY()
	UCoreAttributeSet* CoreAttributeSet;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UUTHUB_ASC* ASC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UGASDataComponent* GASDataComponent;
	
	void SetupAttributeCallbacks();

public:
	// Sets default values for this actor's properties
	ALavaPool();

	FORCEINLINE virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};

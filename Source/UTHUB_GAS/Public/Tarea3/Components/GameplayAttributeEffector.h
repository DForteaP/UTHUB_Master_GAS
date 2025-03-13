#pragma once

#include "CoreMinimal.h"
#include "Tarea3/CoreAttributeSet.h"
#include "UObject/Object.h"
#include "GameplayAttributeEffector.generated.h"



UCLASS(Blueprintable, BlueprintType)
class UTHUB_GAS_API UGameplayAttributeEffector : public UObject
{
	GENERATED_BODY()

public:

	void ApplyAttributeEffector(const FOnAttributeChangeData& InChangeData);

	UFUNCTION(BlueprintImplementableEvent)
	void RecieveApplyAttributeEffector(AActor* InActor, float InNewValue, float InOldValue);
};

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

UCLASS()
class UTHUB_GAS_API AInteractive : public AActor
{
	GENERATED_BODY()

public:
	AInteractive();

	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAction();

	UFUNCTION(BlueprintCallable)
	void CheckTagCondition(AActor* TagOwner);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag ConditionTag;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};

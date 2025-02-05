#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttackBase.generated.h"

UCLASS()
class UTHUB_GAS_API UAttackBase : public UObject
{
	GENERATED_BODY()

public:
	virtual void Attack(AActor* AttackInstigator);
};

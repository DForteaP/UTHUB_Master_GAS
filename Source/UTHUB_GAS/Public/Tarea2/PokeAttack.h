#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "PokeAttack.generated.h"

class UPokeAttack;
class APokemon;

USTRUCT()
struct FAttackAttributes : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)	FName Id;
	UPROPERTY(EditAnywhere)	FText Name;
	UPROPERTY(EditAnywhere)	FText Description;
	UPROPERTY(EditAnywhere)	FGameplayTag Type;
	UPROPERTY(EditAnywhere)	TSubclassOf<UPokeAttack> AttackClass;
	UPROPERTY(EditAnywhere)	float Power;
	UPROPERTY(EditAnywhere)	int32 PP_Max;
};

UCLASS(BlueprintType, Blueprintable)
class UTHUB_GAS_API UPokeAttack : public UObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	FGameplayTag Type;

	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	float AttackDamage;
	
	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	int32 AttackPP;
	
	FAttackAttributes* AttackData;

public:

	virtual void Init(const FAttackAttributes& AttackAttributes);

	virtual void Attack(APokemon* Owner, APokemon* Target);
};

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "PokeAttack.generated.h"

class APokemon;
enum class EPokemonAttack : uint8;

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
	
	FAttackAttributes* AttackData;

public:

	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	FText Name;
	
	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	FGameplayTag Type;

	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	float AttackDamage;
	
	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	int32 AttackPP;

	UPROPERTY(BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	int32 CurrentPP;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPokemonAttack AttackID;
	
	UFUNCTION(BlueprintCallable)
	int GetCurrentPP();

	UFUNCTION(BlueprintCallable)
	void DiscountPP();

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetAttackType();
	
	UFUNCTION(BlueprintCallable)
	int GetAttackPower();
	
	UFUNCTION(BlueprintCallable)
	FText GetAttackName();
	
	virtual void Init(FAttackAttributes* AtrribAttack);
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack(APokemon* Attacker, APokemon* Target);
};

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Pokemon.generated.h"

USTRUCT(BlueprintType)
struct FPokemonTypesEffects : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag TypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, float> Modifier; 
};

UCLASS()
class UTHUB_GAS_API APokemon : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	int32 PP = 4;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	UDataTable* AttackData;

	void InitializeAttacksData();

public:
	APokemon();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	TMap<UPokeAttack*, int32> AttacksSelected;	

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Pokemon)
	APokemon* PokemonTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	TArray<UPokeAttack*> AttackList;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	TArray<FGameplayTag> Type;

	UFUNCTION(BlueprintCallable)
	virtual bool TryDoAttack(UPokeAttack* AttackExecute);
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

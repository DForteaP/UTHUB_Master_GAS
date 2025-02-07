#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Pokemon.generated.h"

class UPokeAttack;

UENUM(BlueprintType)
enum class EPokemonAttack : uint8
{
	Placaje      UMETA(DisplayName = "Placaje"),
	LatigoCepa	 UMETA(DisplayName = "LatigoCepa"),
	Burbuja		 UMETA(DisplayName = "Burbuja"),
	Ascuas		 UMETA(DisplayName = "Ascuas"),
	Impactrueno  UMETA(DisplayName = "Impactrueno")
};

USTRUCT(BlueprintType)
struct FPokemonTypesTable : public FTableRowBase
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	UDataTable* TableTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon, meta=(AllowPrivateAccess = true ))
	UDataTable* AttackTable;
	
	void InitializeAttacksData();

public:
	APokemon();
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category="Pokemon|Combat")
	void Attack1();
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category="Pokemon|Combat")
	void Attack2();
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category="Pokemon|Combat")
	void Attack3();
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category="Pokemon|Combat")
	void Attack4();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Pokemon)
	APokemon* PokemonTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	TArray<EPokemonAttack> AttackList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	TArray<UPokeAttack*> AttacksInstanciated;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	FText PokemonName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	TArray<FGameplayTag> Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	int PSMax;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pokemon)
	int CurrentPS;
	
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayTag> GetTypes();
	
	UFUNCTION(BlueprintCallable)
	void ApplyDamage(APokemon* Attacker, UPokeAttack* DataAttack);

	UFUNCTION(BlueprintCallable)
	float CalculateModifier(UPokeAttack* DataAttack);
	
	UFUNCTION(BlueprintCallable)
	virtual bool TryDoAttack(UPokeAttack* AttackExecute);
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

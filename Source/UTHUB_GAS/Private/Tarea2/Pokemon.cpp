#include "Tarea2/Pokemon.h"
#include "Tarea2/PokeAttack.h"

APokemon::APokemon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APokemon::BeginPlay()
{
	Super::BeginPlay();
	InitializeAttacksData();
}

void APokemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APokemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APokemon::InitializeAttacksData()
{
	for (EPokemonAttack AttackEnum : AttackList)
	{
		FString EnumString = UEnum::GetValueAsString(AttackEnum);
		const FName RowName = *EnumString;
		static const FString ContextString(TEXT("Attack DataTable"));
		FAttackAttributes* FoundRow = AttackTable->FindRow<FAttackAttributes>(RowName, ContextString);
		
		if (FoundRow)
		{
			if (FoundRow->AttackClass)
			{
				UPokeAttack* NewAttack = NewObject<UPokeAttack>(this, FoundRow->AttackClass);
				if (NewAttack)
				{
					NewAttack->Init(FoundRow);
					AttacksInstanciated.Add(NewAttack);
				}
			}
		}
	}
}

TArray<FGameplayTag> APokemon::GetTypes()
{
	return Type;
}

void APokemon::ApplyDamage(APokemon* Attacker, UPokeAttack* DataAttack)
{
	float Modifier = CalculateModifier(DataAttack);
	CurrentPS = CurrentPS - (DataAttack->GetAttackPower() * Modifier);
	
	FString AttackerName = Attacker->GetName();  
	FString AttackerType = "";//Attacker->Type.ToString();
	FString TargetName = this->GetName();
	FString TargetType = "";//this->Type.ToString();
	FString AttackType = DataAttack->Type.ToString(); 
	
	UE_LOG(LogTemp, Log, TEXT("El Pokémon %s (Tipo: %s) lanza un ataque de tipo %s contra %s (Tipo: %s) con un multiplicador de daño de: %.2f"),
		*AttackerName, *AttackerType, *AttackType, *TargetName, *TargetType, Modifier);
}

float APokemon::CalculateModifier(UPokeAttack* DataAttack)
{
	if (!DataAttack || !TableTypes) return 1.0f;

	static const FString ContextString(TEXT("TypeEffectivenessTable"));
	FGameplayTag AttackType = DataAttack->GetAttackType();
	FGameplayTag TargetType1 = Type[0];
	//FGameplayTag TargetType2 = Type[1];
	
	TArray<FName> RowNames = TableTypes->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FPokemonTypesTable* Row = TableTypes->FindRow<FPokemonTypesTable>(RowName, ContextString);
		if (!Row) continue;
		if (const float* Modifier = Row->Modifier.Find(TargetType1))
		{
			return *Modifier;
		}
	}

	return 1.0f;
}


bool APokemon::TryDoAttack(UPokeAttack* AttackExecute)
{
	for (UPokeAttack* Attack : AttacksInstanciated)
	{
		if (Attack->GetName() == AttackExecute->GetName())
		{
			if (Attack->GetCurrentPP() == 0){return false;}
			Attack->Attack(this, PokemonTarget);
			Attack->DiscountPP();
		}
	}
	return false;
}

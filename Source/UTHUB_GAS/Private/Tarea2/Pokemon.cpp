#include "Tarea2/Pokemon.h"
#include "Tarea2/PokeAttack.h"

APokemon::APokemon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APokemon::Attack1()
{
	if (AttacksInstanciated.Num() != 0)
	{
		TryDoAttack(AttacksInstanciated[0]);
	}
}

void APokemon::Attack2()
{
	if (AttacksInstanciated.Num() > 0)
	{
		TryDoAttack(AttacksInstanciated[1]);
	}
}

void APokemon::Attack3()
{
	if (AttacksInstanciated.Num() > 1)
	{
		TryDoAttack(AttacksInstanciated[2]);
	}
}

void APokemon::Attack4()
{
	if (AttacksInstanciated.Num() > 2)
	{
		TryDoAttack(AttacksInstanciated[3]);
	}
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
	
	FString AttackType = DataAttack->Type.ToString(); 
	UE_LOG(LogTemp, Log, TEXT("POKEMON: El Pokémon %s lanza %s, un ataque de tipo %s contra %s con un multiplicador de daño de: %.2f"),
		*Attacker->PokemonName.ToString(), *DataAttack->Name.ToString(), *AttackType, *this->PokemonName.ToString(), Modifier);
}

float APokemon::CalculateModifier(UPokeAttack* DataAttack)
{
	if (!DataAttack || !TableTypes) return 1.0f;

	static const FString ContextString(TEXT("TypeEffectivenessTable"));
	FGameplayTag AttackType = DataAttack->GetAttackType();
	FGameplayTag TargetType1 = Type[0];
	TArray<FName> RowNames = TableTypes->GetRowNames();
	for (const FName& RowName : RowNames)
	{
		FPokemonTypesTable* Row = TableTypes->FindRow<FPokemonTypesTable>(RowName, ContextString);
		if (!Row) continue;
		if (AttackType.MatchesTag(Row->TypeTag))
		{
			if (const float* Modifier = Row->Modifier.Find(TargetType1))
			{
				UE_LOG(LogTemp, Log, TEXT("POKEMON: Modificador encontrado: %.2f"), *Modifier);
				return *Modifier;
			}
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

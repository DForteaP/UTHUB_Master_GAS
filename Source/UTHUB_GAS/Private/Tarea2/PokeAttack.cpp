#include "Tarea2/PokeAttack.h"
#include "Tarea2/Pokemon.h"

struct FPokemonTypesEffects;

void UPokeAttack::Init(FAttackAttributes* AtrribAttack)
{
	UE_LOG(LogTemp, Log, TEXT("El ataque es: %s"), *AtrribAttack->Name.ToString());
}

FText UPokeAttack::GetAttackName()
{
	return Name;
}

int UPokeAttack::GetCurrentPP()
{
	return CurrentPP;
}

void UPokeAttack::DiscountPP()
{
	CurrentPP = CurrentPP - 1;
}

FGameplayTag UPokeAttack::GetAttackType()
{
	return AttackData->Type;
}

int UPokeAttack::GetAttackPower()
{
	return AttackDamage;
}

void UPokeAttack::Attack(APokemon* Attacker, APokemon* Target)
{
	if (!Target){return;}
	Target->ApplyDamage(Attacker, this);
}

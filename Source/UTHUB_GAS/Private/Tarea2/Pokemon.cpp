#include "Tarea2/Pokemon.h"

APokemon::APokemon()
{
	PrimaryActorTick.bCanEverTick = true;
}



void APokemon::BeginPlay()
{
	Super::BeginPlay();
	
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
}

bool APokemon::TryDoAttack(UPokeAttack* AttackExecute)
{
	return true;
}

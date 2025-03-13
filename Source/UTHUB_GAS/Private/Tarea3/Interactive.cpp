#include "Tarea3/Interactive.h"

#include "UTHUB_ASC.h"
#include "UTHUB_GASCharacter.h"

AInteractive::AInteractive()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractive::CheckTagCondition(AActor* TagOwner)
{

	if(UUTHUB_ASC* ASC = TagOwner->FindComponentByClass<UUTHUB_ASC>())
	{
		ASC->AddLooseGameplayTag(ConditionTag);
	}
}

void AInteractive::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


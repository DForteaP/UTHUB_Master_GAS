#include "UTHUB_GAS/Public/UTHUB_ASC.h"

UUTHUB_ASC::UUTHUB_ASC()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUTHUB_ASC::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo(GetOwner(), GetOwner());
}

void UUTHUB_ASC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UUTHUB_ASC::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	//init effect
	//init attribs
	//init skills
}



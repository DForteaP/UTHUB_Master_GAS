// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GASCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "UTHUB_ASC.h"
#include "Tarea3/GameplayStatesManager.h"
#include "Tarea3/Components/GameplayAttributeEffector.h"
#include "Tarea3/Components/GASDataComponent.h"

AUTHUB_GASCharacter::AUTHUB_GASCharacter()
{

	ASC = CreateDefaultSubobject<UUTHUB_ASC>(TEXT("ASC"));
	
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	CoreAttributeSet = CreateDefaultSubobject<UCoreAttributeSet>(TEXT("Core Atrributes"));
	GASDataComponent = CreateDefaultSubobject<UGASDataComponent>(TEXT("GAS Data"));
}

void AUTHUB_GASCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

UAbilitySystemComponent* AUTHUB_GASCharacter::GetAbilitySystemComponent() const
{
	return ASC;
}

void AUTHUB_GASCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(CharacterData)
	{
		TArray<FCharacterAttrib*> OutData;
		CharacterData->GetAllRows(TEXT(""), OutData);

		if(!OutData.IsEmpty())
		{
			FCharacterAttrib** Attr = OutData.FindByPredicate([this](FCharacterAttrib* Row)
			{
				return Row->ClassTag.MatchesTag(CharacterClassTag);
			});
			
			if (Attr)
			{
				CharacterAttributes = *Attr;
			}
			
		}
	}

	SetupAttributeCallbacks();
}

void AUTHUB_GASCharacter::Attack()
{
}

void AUTHUB_GASCharacter::InitializeCharacter()
{
	if(CharacterData)
	{
		TArray<FCharacterAttrib*> OutData;
		CharacterData->GetAllRows(TEXT(""), OutData);

		if(!OutData.IsEmpty())
		{
			FCharacterAttrib** Attr = OutData.FindByPredicate([this](FCharacterAttrib* Row)
			{
				return Row->ClassTag.MatchesTag(CharacterClassTag);
			});
			
			if(Attr) CharacterAttributes = *Attr;
		}

	}
}


void AUTHUB_GASCharacter::SetupAttributeCallbacks()
{
	if (!GASDataComponent || !ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("GASDataComponent o ASC no están inicializados en %s"), *GetName());
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Iniciando SetupAttributeCallbacks en %s"), *GetName());

	int32 EffectorCount = 0;
	for (auto [Attribute, EffectorClass] : GASDataComponent->AttributeEffectors)
	{
		if (!EffectorClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("EffectorClass es nullptr en %s"), *GetName());
			continue;
		}

		UGameplayAttributeEffector* EffectorObject = EffectorClass->GetDefaultObject<UGameplayAttributeEffector>();
		if (!EffectorObject)
		{
			UE_LOG(LogTemp, Error, TEXT("No se pudo obtener el objeto por defecto de %s"), *EffectorClass->GetName());
			continue;
		}

		FOnGameplayAttributeValueChange& Delegate = ASC->GetGameplayAttributeValueChangeDelegate(Attribute);
		Delegate.AddUObject(EffectorObject, &UGameplayAttributeEffector::ApplyAttributeEffector);

		UE_LOG(LogTemp, Log, TEXT("Se ha añadido Effector: %s al atributo %s"), 
			*EffectorClass->GetName(), *Attribute.GetName());

		EffectorCount++;
	}

	UE_LOG(LogTemp, Log, TEXT("Se registraron %d effectors en %s"), EffectorCount, *GetName());
}



void AUTHUB_GASCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayStates;
}

void AUTHUB_GASCharacter::AddTags(const FGameplayTag& InTag)
{
	GameplayStates.AddTag(InTag);
}

void AUTHUB_GASCharacter::RemoveTags(FGameplayTag& InTag)
{
	GameplayStates.RemoveTag(InTag);
}

void AUTHUB_GASCharacter::ApplyGameplayEffects()
{
	if(ASC && SampleEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(SampleEffect, 1, EffectContext);
				
		ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get());
	}
}

void AUTHUB_GASCharacter::Jump()
{
	Super::Jump();

	GameplayStates.RemoveTag(FGameplayStatesManager::Get().Tag_InteractEnabled);
}

void AUTHUB_GASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

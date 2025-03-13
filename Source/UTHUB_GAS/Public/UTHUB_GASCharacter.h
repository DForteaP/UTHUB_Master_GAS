// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "UTHUB_ASC.h"
#include "Tarea3/CoreAttributeSet.h"
#include "Tarea3/GameplayBaseStateTags.h"
#include "UTHUB_GASCharacter.generated.h"

class UAttackBase;

USTRUCT()
struct FCharacterAttrib : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)	FGameplayTag ClassTag;
	UPROPERTY(EditAnywhere)	float Health;
	UPROPERTY(EditAnywhere)	float Strength;
	UPROPERTY(EditAnywhere)	float Speed;
	UPROPERTY(EditAnywhere)	UAnimMontage* AttackAnimation;
	UPROPERTY(EditAnywhere)	TSubclassOf<UAttackBase> PrimaryAttack;
};

UCLASS(Blueprintable)
class AUTHUB_GASCharacter : public ACharacter, public IAbilitySystemInterface, public IGameplayTagCustomInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true ))
	FGameplayTag CharacterClassTag;
	
	FCharacterAttrib* CharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true ))
	UDataTable* CharacterData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true ))
	TSubclassOf<UGameplayEffect> SampleEffect;
	
	UPROPERTY()
	UCoreAttributeSet* CoreAttributeSet;
	
public:
	AUTHUB_GASCharacter();
	
	virtual void Tick(float DeltaSeconds) override;
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Character Attributes")
	float GetHealth() const { return CharacterAttributes ? CharacterAttributes->Health : 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Character Attributes")
	float GetStrength() const { return CharacterAttributes ? CharacterAttributes->Strength : 0.0f; }

	UFUNCTION(BlueprintPure, Category = "Character Attributes")
	float GetSpeed() const { return CharacterAttributes ? CharacterAttributes->Speed : 0.0f; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ActiveEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer GameplayStates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameplayBaseStateTags* CharacterStates;

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	
	virtual void AddTags(const FGameplayTag& InTag) override;
	virtual void RemoveTags(FGameplayTag& InTag) override;

	UFUNCTION(CallInEditor)
	void ApplyGameplayEffects();
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack();
	
	virtual void Jump() override;
	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UUTHUB_ASC* ASC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	class UGASDataComponent* GASDataComponent;
	
	void InitializeCharacter();

	void SetupAttributeCallbacks();
};


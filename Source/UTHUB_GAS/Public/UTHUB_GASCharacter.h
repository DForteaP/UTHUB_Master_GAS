// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
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

class UUTHUB_ASC;

UCLASS(Blueprintable)
class AUTHUB_GASCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true ))
	FGameplayTag CharacterClassTag;
	
	FCharacterAttrib* CharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = true ))
	UDataTable* CharacterData;

public:
	AUTHUB_GASCharacter();

	UUTHUB_ASC* ASC;
	
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

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void Attack();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};


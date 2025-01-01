// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, Category="Attribute")
	float DefaultHealth = 50.f;

	UPROPERTY(EditAnywhere, Category="Attribute")
	float DefaultMaxHealth = 100.f;

	UPROPERTY(EditAnywhere, Category="Attribute")
	float DefaultMana = 50.f;

	UPROPERTY(EditAnywhere, Category="Attribute")
	float DefaultMaxMana = 100.f;

	void InitAbilityActorInfo();
};

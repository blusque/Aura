// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

/**
 * ATTRIBUTE_ACCESSORS is a macro that defines a set of functions to access the attribute.
 * Includes:
 *	- Getter for an attribute.
 *	- Getter for the value of an attribute.
 *	- Setter for the value of an attribute.
 *	- Initializer for the value of an attribute.
 *
 * With 'showdebug abilitysystem' in the cheater in editor, you can see the value of the attributes.
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * When you need to replicate some attributes, you need to implement the function GetLifetimeReplicatedProps.
 * 
 * In GetLifetimeReplicatedProps function, call the macro DOREPLIFETIME_CONDITION_NOTIFY with the attribute you want to
 * replicate.
 * 
 * The c is class name, v is value name, last two is condition and when to notify. COND_None means no condition and will
 * send anytime it changes, and REPNOTIFY_Always means always Call the property's RepNotify function when it is received
 * from the server.
 * 
 * In RepNotify function, whose name obeys the convention of 'OnRep_XXX' where XXX is the attribute name, call the macro
 * GAMEPLAYATTRIBUTE_REPNOTIFY. This macro is used for prediction on client.
 */

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	
	// Always implement this function when you need to replicate some attributes.
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(ReplicatedUsing=OnRep_Health, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(ReplicatedUsing=OnRep_MaxHealth, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(ReplicatedUsing=OnRep_Mana, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(ReplicatedUsing=OnRep_MaxMana, BlueprintReadOnly, Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UFUNCTION()
	void InitDefaultAuraAttributes(float InHealth, float InMaxHealth, float InMana, float InMaxMana);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
};

// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerData
{
	GENERATED_BODY()

	static const FWidgetControllerData Empty;
	
	FWidgetControllerData()
		: PlayerController(nullptr)
		, PlayerState(nullptr)
		, AbilitySystemComponent(nullptr)
		, AttributeSet(nullptr)
	{
	}

	FWidgetControllerData(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerController(PC)
		, PlayerState(PS)
		, AbilitySystemComponent(ASC)
		, AttributeSet(AS)
	{
	}

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet;
};

/**
 * Widget Controller should be related to 4 base models:
 * - PlayerController;
 * - PlayerState;
 * - AbilitySystemComponent;
 * - AttributeSet.
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	void SetData(const FWidgetControllerData& Data);
	virtual void BroadcastInitialValues() {}
	virtual void BindCallbacksToDependencies() {}
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAttributeSet> AttributeSet;
};

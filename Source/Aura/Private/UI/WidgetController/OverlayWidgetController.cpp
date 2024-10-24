// Copyright Blusque Mei


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();

	auto const AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnManaChanged.Broadcast(AS->GetMana());
	OnMaxManaChanged.Broadcast(AS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	auto const AS = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AS->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthChangedCallback);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AS->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthChangedCallback);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AS->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaChangedCallback);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AS->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaChangedCallback);
}

void UOverlayWidgetController::OnHealthChangedCallback(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthChangedCallback(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaChangedCallback(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaChangedCallback(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

// Copyright Blusque Mei


#include "UI/WidgetController/AuraWidgetController.h"

const FWidgetControllerData FWidgetControllerData::Empty;

void UAuraWidgetController::SetData(const FWidgetControllerData& Data)
{
	PlayerController = Data.PlayerController;
	PlayerState = Data.PlayerState;
	AbilitySystemComponent = Data.AbilitySystemComponent;
	AttributeSet = Data.AttributeSet;
}

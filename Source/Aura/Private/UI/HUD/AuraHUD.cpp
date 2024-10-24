// Copyright Blusque Mei


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AuraWidgetController.h"

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("OverlayWidgetClass is not set!"));
	checkf(OverlayWidgetControllerClass, TEXT("OverlayWidgetControllerClass is not set!"));
	
	if (auto const Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass))
	{
		OverlayWidget = Cast<UAuraUserWidget>(Widget);
		
		auto const WidgetControllerData = FWidgetControllerData(PC, PS, ASC, AS);
		auto const WidgetController = GetOverlayWidgetController(WidgetControllerData);
		OverlayWidget->SetWidgetController(WidgetController);
		WidgetController->BroadcastInitialValues();
		
		OverlayWidget->AddToViewport();
	}
}

UAuraWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerData& Data)
{
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UAuraWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetData(Data);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}

void AAuraHUD::SetOverlayWidgetControllerData(const FWidgetControllerData& Data)
{
	GetOverlayWidgetController()->SetData(Data);
}

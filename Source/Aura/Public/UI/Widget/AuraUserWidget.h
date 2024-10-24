// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * Widget Base Class in Aura Project. All widgets in Aura should inherit from this class.
 * UserWidget relays on WidgetController to know changes in the model it related, as well as notify the model about
 * user interactions.
 * UserWidget should know only about the WidgetController, and the WidgetController should know only about the model.
 * UserWidget should not know about the model.
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
};

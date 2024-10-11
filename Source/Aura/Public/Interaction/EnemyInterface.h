// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
// This class is to avoid circular dependency between classes.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// BlueprintNativeEvent is a function that can be overridden in Blueprint.
	// Implement in C++: void HighLightActor_Implementation();
	// Call in C++: IEnemyInterface::Execute_HighLightActor(ActorHowImplementThisInterface);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Hover")
	void HighLightActor();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Hover")
	void UnHighLightActor();
};

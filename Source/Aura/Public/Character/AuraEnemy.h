// Copyright Blusque Mei

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	void HighLightActor_Implementation();
	
	void UnHighLightActor_Implementation();

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighLighted = false;
	
	int32 EnemyRenderCustomDepth = 250;
};

// Copyright Blusque Mei


#include "Aura/Aura.h"
#include "Character/AuraEnemy.h"

void AAuraEnemy::HighLightActor_Implementation()
{
	IEnemyInterface::HighLightActor_Implementation();

	bHighLighted = true;
	
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighLightActor_Implementation()
{
	IEnemyInterface::UnHighLightActor_Implementation();

	bHighLighted = false;
	
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

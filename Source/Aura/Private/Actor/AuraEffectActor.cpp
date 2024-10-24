// Copyright Blusque Mei


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(Mesh);
	Sphere->SetSphereRadius(30.f);
}

void AAuraEffectActor::PostInitProperties()
{
	Super::PostInitProperties();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

void AAuraEffectActor::OnOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Change here to use Gameplay Effect. For now, using const_cast as a hack!
	if (auto const ASCActor = Cast<IAbilitySystemInterface>(OtherActor))
	{
		auto const AttributeSet = Cast<UAuraAttributeSet>(ASCActor->GetAbilitySystemComponent()->GetAttributeSet(
			UAuraAttributeSet::StaticClass()));

		auto MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(MutableAttributeSet->GetHealth() - 50.f);
		MutableAttributeSet->SetMana(MutableAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


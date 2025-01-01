// Copyright Blusque Mei


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilityBlueprint.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Use only a scene component as the root rather than stipulate a mesh and sphere component.
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneComponent"));
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffectClass) const
{
	if (auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		// Crash if the InstantGameplayEffectClass is not set.
		check(GameplayEffectClass)
		
		auto EffectContext = TargetASC->MakeEffectContext();
		EffectContext.AddSourceObject(this);
		auto const GameplayEffectSpec = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContext);
		TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpec.Data.Get());
	}
}


/**
 * It's OK to hard code so many functions in C++. But why not make it more dynamic and flexible in Blueprint?
 * Just create a base C++ framework and let Blueprint do the rest.

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
*/

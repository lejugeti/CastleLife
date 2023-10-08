// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "SpeakToActor.generated.h"

class UTextRenderComponent;

/**
 * 
 */
UCLASS()
class CASTLELIFE_API USpeakToActor : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USpeakToActor();

	UFUNCTION(BlueprintCallable)
	static const FName& GetTag() { return TriggerTag; }
	
protected:
	// inline static const FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Ability.Character.Speak");
	inline static const FName TriggerTag = FName("Ability.Character.Speak");

	UPROPERTY()
	UTextRenderComponent* SpeakingZone;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

};

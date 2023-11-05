// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "SpeakToActor.generated.h"

class ACastleLifeCharacter;
class UConversation;
class UTextRenderComponent;
class ATagCleaner;

/**
 * 
 */
UCLASS()
class CASTLELIFE_API USpeakToActor : public UGameplayAbility
{
	GENERATED_BODY()

public:
	USpeakToActor();

protected:
	inline static const FName TriggerTag = FName("Ability.Character.Speak");

	/**
	 * @see UGameplayAbility#ActivationOwnedTags
	 */
	inline static const TArray<FName> OwnerTagsOnActivation = { TriggerTag };

	/**
	 * @see UGameplayAbility#ActivationBlockedTags
	 */
	inline static const TArray<FName> OwnerBlockingTags = { TriggerTag };

	UPROPERTY(BlueprintReadOnly)
	ATagCleaner* TagCleaner;
	
	UPROPERTY()
	UTextRenderComponent* SpeakingZone;

	/**
	 * Conversation in which speaking happens
	 */
	UPROPERTY()
	UConversation* CurrentConversation;

	/**
	 * Save the last sentence said with this ability
	 */
	UPROPERTY()
	FName LastSentenceTagName;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	/**
	 * Tries to retrieve the character's conversation in which it takes part.
	 * If none exists, the function creates one.
	 */
	UFUNCTION()
	UConversation* GetCharacterConversation(const ACastleLifeCharacter* Character) const;

	UFUNCTION()
	ACastleLifeCharacter* GetOwner(const FGameplayAbilityActorInfo& ActorInformation) const;

	UFUNCTION()
	ATagCleaner* GetTagCleaner();

public:
	UFUNCTION(BlueprintPure)
	static const FName& GetTag() { return TriggerTag; }
};

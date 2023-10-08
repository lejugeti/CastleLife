// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeakToActor.h"
#include "../Characters/Npc_Character.h"
#include "CastleLife/Characters/Sentences/EventReactSentence.h"
#include "Components/TextRenderComponent.h"
#include "Models/GameplayAbilityTargetData_SpeakingData.h"

USpeakToActor::USpeakToActor()
{
	checkf(TriggerTag.IsValid(), TEXT("Le tag de déclenchement de USpeakToActor doit être défini."))
	
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(TriggerTag);
	this->AbilityTriggers.Add(TriggerData);
}

void USpeakToActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	
	const ANpc_Character* Character = Cast<ANpc_Character>(ActorInfo->OwnerActor);
	if(SpeakingZone == nullptr)
	{
		UTextRenderComponent* CharacterSpeakingZone = Cast<UTextRenderComponent>(Character->FindComponentByClass(UTextRenderComponent::StaticClass()));
		SpeakingZone = CharacterSpeakingZone;
	}
	check(SpeakingZone != nullptr)
	
	FGameplayAbilityTargetDataHandle HandleData = TriggerEventData->TargetData;
	FGameplayAbilityTargetData* Data = HandleData.Get(0);

	if(Data != nullptr && Data->GetScriptStruct() == FGameplayAbilityTargetData_SpeakingData::StaticStruct())
	{
		const FGameplayAbilityTargetData_SpeakingData* SpeakingData = StaticCast<FGameplayAbilityTargetData_SpeakingData*>(Data);
		const FEventReactSentence Sentence = Character->GetSpeakPhraseByTagName(SpeakingData->Sentence);
		SpeakingZone->SetText(FText::FromString(Sentence.Sentence));
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USpeakToActor::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) {
	// UE_LOG(LogTemp, Warning, TEXT("USpeakToActor end"));
}


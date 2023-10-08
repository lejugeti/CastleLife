// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityPayloadGenerator.h"

#include "Abilities/GameplayAbilityTypes.h"
#include "CastleLife/Abilities/SpeakToActor.h"
#include "CastleLife/Abilities/Models/GameplayAbilityTargetData_SpeakingData.h"

FGameplayEventData UGameplayAbilityPayloadGenerator::BuildSpeakToActorAbilityPayload(
    AActor* Instigator, const FName& SentenceTagName)
{
    const FGameplayTag AbilityTriggerTag = FGameplayTag::RequestGameplayTag(USpeakToActor::GetTag());

    FGameplayAbilityTargetData_SpeakingData* SpeakingData = new FGameplayAbilityTargetData_SpeakingData();
    SpeakingData->Sentence = SentenceTagName;
    FGameplayAbilityTargetDataHandle DataHandle;
    DataHandle.Add(SpeakingData);
	
    FGameplayEventData Payload;
    Payload.EventTag = AbilityTriggerTag;
    Payload.Instigator = Instigator;
    Payload.TargetData = DataHandle;

    return Payload;
}

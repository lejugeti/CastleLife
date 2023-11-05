// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "CastleLife/Characters/CastleLifeCharacter.h"
#include "CastleLife/Characters/Conversations/Conversation.h"
#include "CastleLife/Characters/Conversations/SpeakingAttitude.h"
#include "GameplayAbilityTargetData_SpeakingData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CASTLELIFE_API FGameplayAbilityTargetData_SpeakingData : public FGameplayAbilityTargetData
{
    GENERATED_USTRUCT_BODY()

public:

    FGameplayAbilityTargetData_SpeakingData(): SpeakingAttitude(ESpeakingAttitude::Normal), Conversation(nullptr) {}
    
    UPROPERTY()
    FName SentenceTagName;

    UPROPERTY()
    ESpeakingAttitude SpeakingAttitude;
    
    /**
     * Receivers to which the sentence is directed
     */
    UPROPERTY()
    TSet<ACastleLifeCharacter*> Receivers;

    /**
     * Conversation in which the sentence takes place
     */
    UPROPERTY()
    UConversation* Conversation;

    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    }
};

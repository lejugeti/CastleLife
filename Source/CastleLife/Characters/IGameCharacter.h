// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Sentences/EventReactSentence.h"
#include "UObject/Object.h"
#include "IGameCharacter.generated.h"

/**
 * 
 */
UINTERFACE(BlueprintType)
class UGameCharacter : public UInterface
{
    GENERATED_BODY()
};

class IGameCharacter
{
    GENERATED_BODY()

public:
    UFUNCTION()
    virtual FEventReactSentence GetSpeakPhraseByTagName(const FName& SentenceTagName) const
    {
        checkf(false, TEXT("Method GetSpeakPhraseByTagName is not yet implemented"))
        return FEventReactSentence();
    };

    UFUNCTION()
    virtual FEventReactSentence GetSpeakPhraseByTag(const FGameplayTag& SentenceTag) const
    {
        checkf(false, TEXT("Method GetSpeakPhraseByTag is not yet implemented"))
        return FEventReactSentence();
    };

};


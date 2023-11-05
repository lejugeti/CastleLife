// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CastleLife/Characters/CastleLifeCharacter.h"
#include "UObject/Object.h"
#include "Conversation.generated.h"

/**
 * 
 */
UCLASS()
class CASTLELIFE_API UConversation : public UObject
{
    GENERATED_BODY()

protected:
    UPROPERTY()
    TSet<ACastleLifeCharacter*> Protagonists;

public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TSet<ACastleLifeCharacter*> GetProtagonists();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    int AddProtagonist(ACastleLifeCharacter* NewProtagonist);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    int AddAllProtagonists(const TSet<ACastleLifeCharacter*>& NewProtagonists);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool Includes(const ACastleLifeCharacter* Character) const;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterUseSentence, FName, SentenceTagName,
                                                   ACastleLifeCharacter*,
                                                   Emitter, UConversation*, Conversation);

    UPROPERTY(BlueprintAssignable, Category = "Speak Event")
    FOnCharacterUseSentence OnCharacterStartSpeaking;

    UFUNCTION(BlueprintCallable)
    void BindCharacterToOnCharacterStartSpeaking(ACastleLifeCharacter* Listener);

    UFUNCTION(BlueprintCallable)
    void NotifyOnCharacterStartSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                      UConversation* Conversation) const;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterEndSpeaking, FName, SentenceTagName,
                                               ACastleLifeCharacter*,
                                               Emitter, UConversation*, Conversation);

    UPROPERTY(BlueprintAssignable, Category = "Speak Event")
    FOnCharacterEndSpeaking OnCharacterEndSpeaking;

    UFUNCTION(BlueprintCallable)
    void BindCharacterToOnCharacterEndSpeaking(ACastleLifeCharacter* Listener);

    UFUNCTION(BlueprintCallable)
    void NotifyOnCharacterEndSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                      UConversation* Conversation) const;
};

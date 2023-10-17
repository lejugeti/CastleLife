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
    TArray<ACastleLifeCharacter*> Protagonists;

    UPROPERTY()
    TArray<FString> Strings;
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<ACastleLifeCharacter*> GetProtagonists();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    TArray<FString> GetStrings()
    {
        return Strings;
    }

    UFUNCTION(BlueprintCallable, BlueprintPure)
    int AddProtagonist(ACastleLifeCharacter* NewProtagonist);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    int AddAllProtagonists(const TArray<ACastleLifeCharacter*>& NewProtagonists);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    bool Includes(const ACastleLifeCharacter* Character) const;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterUseSentence, FName, SentenceTagName,
                                                   ACastleLifeCharacter*,
                                                   Emitter, UConversation*, Conversation);

    UPROPERTY(BlueprintAssignable, Category = "Speak Event")
    FOnCharacterUseSentence OnCharacterUseSentence;

    UFUNCTION(BlueprintCallable)
    void BindCharacterToOnCharacterUseSentence(ACastleLifeCharacter* Listener);

    UFUNCTION(BlueprintCallable)
    void BindCharacterListToOnCharacterUseSentence(const TArray<ACastleLifeCharacter*>& Listeners);

    UFUNCTION(BlueprintCallable)
    void NotifyOnCharacterUseSentence(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                      UConversation* Conversation) const;
};

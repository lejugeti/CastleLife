// Fill out your copyright notice in the Description page of Project Settings.


#include "Conversation.h"

TSet<ACastleLifeCharacter*> UConversation::GetProtagonists()
{
    return Protagonists;
}

int UConversation::AddProtagonist(ACastleLifeCharacter* NewProtagonist)
{
    if (!Protagonists.Contains(NewProtagonist))
    {
        Protagonists.Add(NewProtagonist);
        BindCharacterToOnCharacterUseSentence(NewProtagonist);
    }

    return Protagonists.Num();
}

int UConversation::AddAllProtagonists(const TSet<ACastleLifeCharacter*>& NewProtagonists)
{
    Protagonists.Append(NewProtagonists);
    BindCharacterListToOnCharacterUseSentence(NewProtagonists);
    return Protagonists.Num();
}

bool UConversation::Includes(const ACastleLifeCharacter* Character) const
{
    return Protagonists.Contains(Character);
}

void UConversation::BindCharacterToOnCharacterUseSentence(ACastleLifeCharacter* Listener)
{
    TScriptDelegate<> Delegate;
    Delegate.BindUFunction(Listener, FName("HandleSentenceUsed"));
    OnCharacterUseSentence.AddUnique(Delegate);
}

void UConversation::BindCharacterListToOnCharacterUseSentence(const TSet<ACastleLifeCharacter*>& Listeners)
{
    for (const auto& Listener : Listeners)
    {
        TScriptDelegate<> Delegate;
        Delegate.BindUFunction(Listener, FName("HandleOnCharacterSpoke"));
        OnCharacterUseSentence.AddUnique(Delegate);
    }
}

void UConversation::NotifyOnCharacterUseSentence(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                                 UConversation* Conversation) const
{
    OnCharacterUseSentence.Broadcast(SentenceTagName, Emitter, Conversation);
}

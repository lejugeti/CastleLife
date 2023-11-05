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
        BindCharacterToOnCharacterStartSpeaking(NewProtagonist);
        BindCharacterToOnCharacterEndSpeaking(NewProtagonist);
    }

    return Protagonists.Num();
}

int UConversation::AddAllProtagonists(const TSet<ACastleLifeCharacter*>& NewProtagonists)
{
    for(ACastleLifeCharacter* Character : NewProtagonists)
    {
        this->AddProtagonist(Character);
    }

    return Protagonists.Num();
}

bool UConversation::Includes(const ACastleLifeCharacter* Character) const
{
    return Protagonists.Contains(Character);
}

void UConversation::BindCharacterToOnCharacterStartSpeaking(ACastleLifeCharacter* Listener)
{
    TScriptDelegate<> Delegate;
    Delegate.BindUFunction(Listener, FName("HandleOnCharacterStartSpeaking"));
    OnCharacterStartSpeaking.AddUnique(Delegate);
}

void UConversation::NotifyOnCharacterStartSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                                   UConversation* Conversation) const
{
    OnCharacterStartSpeaking.Broadcast(SentenceTagName, Emitter, Conversation);
}

void UConversation::BindCharacterToOnCharacterEndSpeaking(ACastleLifeCharacter* Listener)
{
    TScriptDelegate<> Delegate;
    Delegate.BindUFunction(Listener, FName("HandleOnCharacterEndSpeaking"));
    OnCharacterEndSpeaking.AddUnique(Delegate);
}

void UConversation::NotifyOnCharacterEndSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                                 UConversation* Conversation) const
{
    OnCharacterEndSpeaking.Broadcast(SentenceTagName, Emitter, Conversation);
}
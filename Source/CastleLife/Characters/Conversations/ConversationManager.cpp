// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationManager.h"

#include "Conversation.h"


// Sets default values
AConversationManager::AConversationManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AConversationManager::BeginPlay()
{
    Super::BeginPlay();

    Conversations.Empty();    
}

// Called every frame
void AConversationManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

UConversation* AConversationManager::CreateConversation()
{
    UConversation* NewConversation = NewObject<UConversation>();
    Conversations.Add(NewConversation);
    return NewConversation;
}

bool AConversationManager::IsPartOfAConversation(const ACastleLifeCharacter* Character)
{
    bool IsPartOfConversation = false;

    TArray<UConversation>::SizeType IndexFindConversation = 0;
    while(!IsPartOfConversation && IndexFindConversation < Conversations.Num())
    {
        ++IndexFindConversation;
        UConversation* Conversation = Conversations[IndexFindConversation];
        IsPartOfConversation = Conversation->Includes(Character);
    }
    
    return IsPartOfConversation;
}

UConversation* AConversationManager::GetConversationByCharacter(const ACastleLifeCharacter* Character)
{
    UConversation* CharacterConversation = nullptr;

    for(const auto& Conversation: Conversations)
    {
        if(Conversation->Includes(Character))
        {
            checkf(CharacterConversation == nullptr, TEXT("The character is part of multiple conversations."))
            CharacterConversation = Conversation;
        }
    }

    return CharacterConversation;
}

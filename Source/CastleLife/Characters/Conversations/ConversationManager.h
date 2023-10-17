// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConversationManager.generated.h"

class ACastleLifeCharacter;
class UConversation;

UCLASS()
class CASTLELIFE_API AConversationManager : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AConversationManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadWrite, Category="Conversation")
    TArray<UConversation*> Conversations;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Conversation")
    UConversation* CreateConversation();

    UFUNCTION(BlueprintCallable, Category="Conversation")
    bool IsPartOfAConversation(const ACastleLifeCharacter* Character);

    /**
     * Tries to retrieve the conversation in which the character takes part.
     * @param Character Potential protagonist of a conversation.
     * @return The character's conversation if found, otherwise nullptr.
     */
    UFUNCTION(BlueprintCallable, Category="Conversation")
    UConversation* GetConversationByCharacter(const ACastleLifeCharacter* Character);

};

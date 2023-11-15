// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "IGameCharacter.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "CastleLifeCharacter.generated.h"

class UConversation;
class UAbilitySystemComponent;

UCLASS()
class CASTLELIFE_API ACastleLifeCharacter : public ACharacter, public IGameCharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACastleLifeCharacter();

    // Necessary in order to be used in {@link TSet}
    UE_NODISCARD FORCEINLINE bool operator==(const ACastleLifeCharacter& Other) const
    {
        return this->Name == Other.Name;
    }

    // Necessary in order to be used in {@link TSet}
    friend FORCEINLINE uint32 GetTypeHash(const ACastleLifeCharacter& Character)
    {
        return FCrc::TypeCrc32(Character);
    }

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

    /**
     * Supposed to be unique for each character
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Name")
    FName Name;

    /**
     * \brief Data representing character's sentences
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Speaking Data")
    UDataTable* SpeakingDataTable;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    FName GetCharacterName() const;
    
    /**
    * Get any owned gameplay tags on the asset
    * 
    * @param OutTags	[OUT] Set of tags on the asset
    */
    UFUNCTION(BlueprintCallable, Category = GameplayTags)
    virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
    
    UFUNCTION(BlueprintCallable)
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable)
    virtual FEventReactSentence GetSpeakPhraseByTag(const FGameplayTag& SentenceTag) const override;

    UFUNCTION(BlueprintCallable)
    virtual FEventReactSentence GetSpeakPhraseByTagName(const FName& SentenceTagName) const override;

    UFUNCTION(BlueprintCallable)
    virtual TArray<FEventReactSentence> GetSpeakPhraseListByTagName(const FName& SentenceTagName) const override;

    /**
     * Handle to when a character starts speaking
     * @param SentenceTagName Tag name of the sentence spoken
     * @param Emitter Character which emitted the sentence
     * @param Conversation Current conversation in which the character speaks
     * @see UConversation#OnCharacterStartSpeaking
     */
    UFUNCTION(BlueprintNativeEvent)
    void HandleOnCharacterStartSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                        UConversation* Conversation);

    /**
     * Handle to when a character ends speaking
     * @param SentenceTagName Tag name of the sentence spoken
     * @param Emitter Character which emitted the sentence
     * @param Conversation Current conversation in which the character spoke
     * @see UConversation#OnCharacterEndSpeaking
     */
    UFUNCTION(BlueprintNativeEvent)
    void HandleOnCharacterEndSpeaking(const FName& SentenceTagName, ACastleLifeCharacter* Emitter,
                                      UConversation* Conversation);
};

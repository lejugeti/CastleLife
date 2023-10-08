// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "IGameCharacter.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "CastleLifeCharacter.generated.h"

class UAbilitySystemComponent;

UCLASS()
class CASTLELIFE_API ACastleLifeCharacter : public ACharacter, public IGameCharacter, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACastleLifeCharacter();

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
    UAbilitySystemComponent* AbilitySystemComponent;

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

    UFUNCTION(BlueprintCallable)
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION(BlueprintCallable)
    virtual FEventReactSentence GetSpeakPhraseByTag(const FGameplayTag& SentenceTag) const override;
    
    UFUNCTION(BlueprintCallable)
    virtual FEventReactSentence GetSpeakPhraseByTagName(const FName& SentenceTagName) const override;

    // Delegates for actor communication
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSpeak, FGameplayTag, SentenceTag);

    UPROPERTY(BlueprintAssignable, Category = "Speak Event")
    FOnCharacterSpeak OnCharacterSpeak;

    virtual void BindToOnCharacterSpeak(const ACastleLifeCharacter* Character);

    virtual void NotifyOnCharacterEndSpeaking(FGameplayTag SentenceTag);
    
};

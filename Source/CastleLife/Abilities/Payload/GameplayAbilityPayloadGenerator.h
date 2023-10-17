// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "UObject/Object.h"
#include "GameplayAbilityPayloadGenerator.generated.h"

class ACastleLifeCharacter;
/**
 * 
 */
UCLASS()
class CASTLELIFE_API UGameplayAbilityPayloadGenerator : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="Ability Payload")
    static FGameplayEventData BuildSpeakToActorAbilityPayload(ACastleLifeCharacter* Instigator, const TSet<ACastleLifeCharacter*>& Receivers, const FName& SentenceTagName);
};

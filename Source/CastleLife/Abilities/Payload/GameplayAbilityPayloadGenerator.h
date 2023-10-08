// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "UObject/Object.h"
#include "GameplayAbilityPayloadGenerator.generated.h"

/**
 * 
 */
UCLASS()
class CASTLELIFE_API UGameplayAbilityPayloadGenerator : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category="Ability Payload")
    static FGameplayEventData BuildSpeakToActorAbilityPayload(AActor* Instigator, const FName& SentenceTagName);
};

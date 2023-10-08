// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "GameplayAbilityTargetData_SpeakingData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct CASTLELIFE_API FGameplayAbilityTargetData_SpeakingData : public FGameplayAbilityTargetData
{
    GENERATED_USTRUCT_BODY()

public:

    FGameplayAbilityTargetData_SpeakingData() {}
    
    UPROPERTY()
    FName Sentence;

    virtual UScriptStruct* GetScriptStruct() const override
    {
        return StaticStruct();
    }
};

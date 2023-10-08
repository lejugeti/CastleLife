// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "TagSearcher.generated.h"

/**
 * 
 */
UCLASS()
class CASTLELIFE_API UTagSearcher : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, BlueprintCallable)
    static FGameplayTag FindTagByString(const FString& TagString, bool MatchPartialString = false);
};

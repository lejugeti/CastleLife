// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TagMapper.generated.h"

struct FGameplayTag;
struct FGameplayTagContainer;
/**
 * Mapper working around {@link FGameplayTag}
 */
UCLASS()
class CASTLELIFE_API UTagMapper : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE FGameplayTag ToTag(const FName& TagName);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE TArray<FGameplayTag> ToTagArray(const TArray<FName>& TagNames);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FORCEINLINE FGameplayTagContainer ToTagContainer(const TArray<FName>& TagNames);
};

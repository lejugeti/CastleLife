// Fill out your copyright notice in the Description page of Project Settings.


#include "TagMapper.h"

#include "GameplayTagContainer.h"

FGameplayTag UTagMapper::ToTag(const FName& TagName)
{
    return FGameplayTag::RequestGameplayTag(TagName);
}

TArray<FGameplayTag> UTagMapper::ToTagArray(const TArray<FName>& TagNames)
{
    TArray<FGameplayTag> Tags;
    for(const FName& TagName : TagNames)
    {
        Tags.Add(ToTag(TagName));
    }
    return Tags;
}

FGameplayTagContainer UTagMapper::ToTagContainer(const TArray<FName>& TagNames)
{
    return FGameplayTagContainer::CreateFromArray(ToTagArray(TagNames));
}

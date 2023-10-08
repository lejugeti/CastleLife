// Fill out your copyright notice in the Description page of Project Settings.


#include "TagSearcher.h"

#include "GameplayTagsManager.h"

FGameplayTag UTagSearcher::FindTagByString(const FString& TagString, const bool MatchPartialString)
{
    const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
    FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

    if (!Tag.IsValid() && MatchPartialString)
    {
        FGameplayTagContainer AllTags;
        Manager.RequestAllGameplayTags(AllTags, true);

        for (const FGameplayTag& TestTag : AllTags)
        {
            if (TestTag.ToString().Contains(TagString))
            {
                UE_LOG(LogTemp, Warning, TEXT("Could not find exact match for tag [%s] but found partial match on tag [%s]."), *TagString, *TestTag.ToString());
                Tag = TestTag;
                break;
            }
        }
    }

    return Tag;
}

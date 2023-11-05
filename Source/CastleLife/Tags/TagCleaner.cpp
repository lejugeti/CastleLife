// Fill out your copyright notice in the Description page of Project Settings.


#include "TagCleaner.h"

#include "AbilitySystemComponent.h"
#include "CastleLife/Characters/CastleLifeCharacter.h"


// Sets default values
ATagCleaner::ATagCleaner()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATagCleaner::BeginPlay()
{
    Super::BeginPlay();

    check(Identifier.IsValid())
    Tags.Add(Identifier.GetTagName());
}

// Called every frame
void ATagCleaner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATagCleaner::RemoveGameplayAbilityTag(ACastleLifeCharacter* Character, FName TagName) const
{
    const FGameplayTag Tag = FGameplayTag::RequestGameplayTag(TagName);
    Character->GetAbilitySystemComponent()->RemoveLooseGameplayTag(Tag);
}

void ATagCleaner::RemoveGameplayAbilityTags(ACastleLifeCharacter* Character, TArray<FName> TagNames) const
{
    TArray<FGameplayTag> TagsToRemove;
    for(const FName& Name: TagNames)
    {
        TagsToRemove.Add(FGameplayTag::RequestGameplayTag(Name));
    }
    const FGameplayTagContainer TagContainer = FGameplayTagContainer::CreateFromArray(TagsToRemove);
    Character->GetAbilitySystemComponent()->RemoveLooseGameplayTags(TagContainer);
}


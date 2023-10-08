// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "EventReactSentence.generated.h"

/**
 * A sentence data row that a npc can use in reaction to a tag represented by the Name column
 */
USTRUCT(BlueprintType)
struct FEventReactSentence : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    FEventReactSentence()
    : Sentence("")
    {}

    /** The 'Name' column is the same as the Event Reaction Tag */

    /** Sentence that the NPC can say in reaction to the Tag represented by the row name */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=ReactionSentence)
    FString Sentence;
};

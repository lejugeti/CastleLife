// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "NativeGameplayTags.h"

namespace CastleLifeGameplayTags
{
	CASTLELIFE_API	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	// Declare all of the custom native tags that CastleLife will use
	CASTLELIFE_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Character_Speak);

	/*// These are mappings from MovementMode enums to GameplayTags associated with those enums (below)
	LYRAGAME_API	extern const TMap<uint8, FGameplayTag> MovementModeTagMap;
	LYRAGAME_API	extern const TMap<uint8, FGameplayTag> CustomMovementModeTagMap;

	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Walking);
	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_NavWalking);
	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Falling);
	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Swimming);
	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Flying);

	LYRAGAME_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Movement_Mode_Custom);*/
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpeakingAttitude.generated.h"

UENUM(BlueprintType)
enum class ESpeakingAttitude: uint8
{
    Normal,
    Happy,
    Angry,
    Disgusted,
};

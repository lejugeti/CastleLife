// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TagCleaner.generated.h"

class ACastleLifeCharacter;

UCLASS()
class CASTLELIFE_API ATagCleaner : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ATagCleaner();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /**
     * Used for dependency injection
     */
    UPROPERTY(EditDefaultsOnly)
    FGameplayTag Identifier;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void RemoveGameplayAbilityTag(ACastleLifeCharacter* Character, FName TagName) const;

    UFUNCTION(BlueprintCallable)
    void RemoveGameplayAbilityTags(ACastleLifeCharacter* Character, TArray<FName> TagNames) const;
};

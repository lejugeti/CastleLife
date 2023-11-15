// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HudMessagePoster.generated.h"

class UDialogMessageWidget;
class UDialogBoxWidget;

UCLASS()
class CASTLELIFE_API AHudMessagePoster : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AHudMessagePoster();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY()
    UDialogBoxWidget* DialogBoxWidget;

    UFUNCTION()
    UDialogBoxWidget* GetDialogBox();

    UFUNCTION()
    void DeleteMessageFromHud(UDialogMessageWidget* MessageWidget) const;

    UFUNCTION()
    void ScheduleToDeleteMessageFromHud(UDialogMessageWidget* MessageWidget);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category="Dialog Message")
    void AddMessage(const FText& Message);
};

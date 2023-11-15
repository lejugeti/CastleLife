// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogMessageWidget.h"
#include "Blueprint/UserWidget.h"
#include "DialogBoxWidget.generated.h"

/**
 * 
 */
UCLASS()
class CASTLELIFE_API UDialogBoxWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Dialog Box")
    void AddMessage(const FText& MessageText);
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Dialog Box")
    void RemoveMessage(const UDialogMessageWidget* DialogMessage);

    DECLARE_DELEGATE_OneParam(OnMessageAddedDelegate, UDialogMessageWidget*)
    OnMessageAddedDelegate OnMessageAdded;

    UFUNCTION(BlueprintCallable)
    void NotifyOnMessageAdded(UDialogMessageWidget* MessageWidget)
    {
        OnMessageAdded.ExecuteIfBound(MessageWidget);
    }
};

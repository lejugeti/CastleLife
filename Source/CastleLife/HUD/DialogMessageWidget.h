// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogMessageWidget.generated.h"

/**
 * 
 */
UCLASS()
class CASTLELIFE_API UDialogMessageWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UDialogMessageWidget(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void NativeConstruct() override;

public:
    UFUNCTION()
    virtual bool Initialize() override;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent,Category="Dialog Message")
    void SetMessage(const FText& Message);
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "HudMessagePoster.h"

#include "DialogBoxWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


// Sets default values
AHudMessagePoster::AHudMessagePoster()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHudMessagePoster::BeginPlay()
{
    Super::BeginPlay();
    
}

UDialogBoxWidget* AHudMessagePoster::GetDialogBox()
{
    if(DialogBoxWidget == nullptr)
    {
        UWorld* World = GetWorld();
        check(World != nullptr)

        TArray<UUserWidget*> WidgetsFound;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(World, WidgetsFound, UDialogBoxWidget::StaticClass(), false);
        check(WidgetsFound.Num() == 1)
        DialogBoxWidget = Cast<UDialogBoxWidget>(WidgetsFound[0]);

        DialogBoxWidget->OnMessageAdded.BindUObject(this, &AHudMessagePoster::ScheduleToDeleteMessageFromHud);
    }

    check(DialogBoxWidget != nullptr)
    return DialogBoxWidget;
}

void AHudMessagePoster::DeleteMessageFromHud(UDialogMessageWidget* MessageWidget) const
{
    DialogBoxWidget->RemoveMessage(MessageWidget);
}

void AHudMessagePoster::ScheduleToDeleteMessageFromHud(UDialogMessageWidget* MessageWidget)
{
    FTimerHandle DeleteMessageHandle;
    FTimerDelegate DeleteMessageDelegate;
    DeleteMessageDelegate.BindUObject(this, &AHudMessagePoster::DeleteMessageFromHud, MessageWidget);
    GetWorldTimerManager().SetTimer(DeleteMessageHandle, DeleteMessageDelegate, 3.0f, false);
}

void AHudMessagePoster::AddMessage(const FText& Message)
{
    GetDialogBox()->AddMessage(Message);
}

// Called every frame
void AHudMessagePoster::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


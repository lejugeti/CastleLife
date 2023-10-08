// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Calendar.h"
#include "CastleLifeCharacter.h"
#include "Npc_Character.generated.h"

class UAbilitySystemComponent;
class ATextRenderActor;

UCLASS()
class CASTLELIFE_API ANpc_Character : public ACastleLifeCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANpc_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UCalendar* Calendar;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Schedule")
	void OnNewScheduleEventNotification();
	
public:	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

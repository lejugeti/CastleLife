// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "../Global/Clock.h"

#include "Calendar.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CASTLELIFE_API UCalendar : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCalendar();

	void Initialize(const AClock* WorldClock);

	DECLARE_DELEGATE(FNpcActionDelegate);

	FNpcActionDelegate NpcDelegate;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	const AClock* Clock;

	FTimerHandle CheckDateTimer;

	FTimerDelegate CheckDateDelegate;

	void CheckNpcSchedule();

	void NotifyNpcForNextEvent();


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool IsValid() const;
};

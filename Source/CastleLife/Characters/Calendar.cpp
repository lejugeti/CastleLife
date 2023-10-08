// Fill out your copyright notice in the Description page of Project Settings.


#include "Calendar.h"

// Sets default values for this component's properties
UCalendar::UCalendar()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UCalendar::Initialize(const AClock* WorldClock)
{
	Clock = WorldClock;
}

// Called when the game starts
void UCalendar::BeginPlay()
{
	Super::BeginPlay();

	CheckDateDelegate.BindUObject(this, &UCalendar::CheckNpcSchedule);
	GetOuter()->GetWorld()->GetTimerManager().SetTimer(CheckDateTimer, CheckDateDelegate, 5.0f, true);
}


// Called every frame
void UCalendar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCalendar::CheckNpcSchedule() {
	FDateTime newDummyEventDate(1100, 01, 01, 10, 11, 12, 13);
	//bool nextEventShouldHappen = Clock->GetDateTime() > newDummyEventDate;
	bool nextEventShouldHappen = newDummyEventDate > newDummyEventDate;

	if (nextEventShouldHappen) {
		NotifyNpcForNextEvent();
	}
}

void UCalendar::NotifyNpcForNextEvent() {
	// TODO: Passer le prochain �v�nement au png via le delegate
	if (npcDelegate.IsBound()) {
		GEngine->AddOnScreenDebugMessage(-2, 3.0f, FColor::Red, TEXT("throw event"));
		npcDelegate.ExecuteIfBound();
	} else {
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "NotifyNpcForNextEvent not bound.");
	}
}

bool UCalendar::IsValid() const {
	return clock != nullptr;
}

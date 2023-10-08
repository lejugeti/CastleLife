// Fill out your copyright notice in the Description page of Project Settings.

#include "Clock.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DateTime = new FDateTime(1200, 01, 01, 10, 11, 12, 13);
}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	Super::BeginPlay();

	IncrementDelegate.BindUFunction(this, FName("IncrementDateTime"));
	GetWorldTimerManager().SetTimer(Timer, IncrementDelegate, 10.0f, true);
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AClock::IncrementDateTime() {
	*DateTime += FTimespan::FromMinutes(MinuteIncrement);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, DateTime->ToString());
}

const FDateTime AClock::GetDateTime() const {
	return *DateTime;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Npc_Character.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ANpc_Character::ANpc_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Calendar = CreateDefaultSubobject<UCalendar>(TEXT("Calendar"));
}

// Called when the game starts or when spawned
void ANpc_Character::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld()) {
		TArray<AActor*> WorldClockFound;
		UGameplayStatics::GetAllActorsOfClass(World, AClock::StaticClass(), WorldClockFound);
		check(WorldClockFound.Num() == 1)
		const AClock* WorldClock = Cast<AClock>(WorldClockFound[0]);
		Calendar->Initialize(WorldClock);
		Calendar->NpcDelegate.BindUObject(this, &ANpc_Character::OnNewScheduleEventNotification);
		checkf(Calendar->IsValid(), TEXT("Calendar clock must be initialized."))
	}
}

// Called every frame
void ANpc_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANpc_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
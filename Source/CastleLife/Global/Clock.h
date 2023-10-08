// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Clock.generated.h"


UCLASS()
class CASTLELIFE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

protected:
	const int MinuteIncrement = 10;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FDateTime* DateTime;

	FTimerHandle Timer;

	FTimerDelegate IncrementDelegate;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void IncrementDateTime();

	UFUNCTION(BlueprintCallable, Category="Date")
	const FDateTime GetDateTime() const;
};

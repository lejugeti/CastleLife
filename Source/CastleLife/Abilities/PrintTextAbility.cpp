// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintTextAbility.h"

void UPrintTextAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	// UE_LOG(LogTemp, Warning, TEXT("L'ability fonctionne."));
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);

}

void UPrintTextAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) {
	// UE_LOG(LogTemp, Warning, TEXT("End abilityow"));
}

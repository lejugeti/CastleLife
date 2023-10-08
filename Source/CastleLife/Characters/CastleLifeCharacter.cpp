// Fill out your copyright notice in the Description page of Project Settings.


#include "CastleLifeCharacter.h"

#include "AbilitySystemComponent.h"
#include "CastleLife/Abilities/SpeakToActor.h"


// Sets default values
ACastleLifeCharacter::ACastleLifeCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(false);
}

// Called when the game starts or when spawned
void ACastleLifeCharacter::BeginPlay()
{
    Super::BeginPlay();

    AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(USpeakToActor::StaticClass()));
	
    // FGameplayTag SpeakTag = FGameplayTag::RequestGameplayTag("Ability.Character.Speak");
    // FGameplayAbilityTargetData_SpeakingData* SpeakingData = new FGameplayAbilityTargetData_SpeakingData();
    // SpeakingData->SentenceTag = FGameplayTag::RequestGameplayTag("Test.Speak.2");
    //
    // FGameplayAbilityTargetDataHandle Handle;
    // Handle.Add(SpeakingData);
    //
    // FGameplayEventData Data;
    // Data.EventTag = SpeakTag;
    // Data.Instigator = this;
    // Data.OptionalObject = TObjectPtr<UObject>(this);
    // Data.TargetData = Handle;
	
    // UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SpeakTag, Data);

}

// Called every frame
void ACastleLifeCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACastleLifeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACastleLifeCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

FEventReactSentence ACastleLifeCharacter::GetSpeakPhraseByTag(const FGameplayTag& SentenceTag) const
{
    return GetSpeakPhraseByTagName(SentenceTag.GetTagName());
}

FEventReactSentence ACastleLifeCharacter::GetSpeakPhraseByTagName(const FName& SentenceTagName) const
{
    FEventReactSentence* Sentence = SpeakingDataTable->FindRow<FEventReactSentence>(SentenceTagName, FString("GetSpeakPhrase"));
    return *Sentence;
}

void ACastleLifeCharacter::BindToOnCharacterSpeak(const ACastleLifeCharacter* Character) {
    // TScriptDelegate BindFunction;
    // BindFunction.BindUFunction(NpcCharacter, )
    // OnCharacterSpeak.Add()
}

void ACastleLifeCharacter::NotifyOnCharacterEndSpeaking(const FGameplayTag SentenceTag) {
    OnCharacterSpeak.Broadcast(SentenceTag);
}

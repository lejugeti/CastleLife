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

    checkf(!Name.IsNone(), TEXT("The character name must be defined."))
    
    AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(USpeakToActor::StaticClass()));
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

TArray<FEventReactSentence> ACastleLifeCharacter::GetSpeakPhraseListByTagName(const FName& SentenceTagName) const
{
    TArray<FEventReactSentence> Sentences;
    const TArray<FName> RowNames = SpeakingDataTable->GetRowNames();

    for (const FName& RowName : RowNames)
    {
        const FString Regex = FString::Printf(TEXT("^Conversation.ReactTo.%s"), *SentenceTagName.ToString());
        
        if(FRegexMatcher Matcher(FRegexPattern(Regex), RowName.ToString());
            Matcher.FindNext())
        {
            const FEventReactSentence* Sentence = SpeakingDataTable->FindRow<FEventReactSentence>(RowName, FString("GetSpeakPhraseListByTagName"));
            Sentences.Add(*Sentence);
        }
    }
    
    return Sentences;
}

void ACastleLifeCharacter::HandleOnCharacterSpoke(const FName& SentenceTagName, ACastleLifeCharacter* Emitter)
{
    if(Name != Emitter->Name)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character %s : HandleSentenceUsed"), *Name.ToString());
        
    }
}

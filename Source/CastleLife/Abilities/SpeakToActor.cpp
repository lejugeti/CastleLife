// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeakToActor.h"
#include "../Characters/Npc_Character.h"
#include "CastleLife/Characters/Conversations/Conversation.h"
#include "CastleLife/Characters/Conversations/ConversationManager.h"
#include "CastleLife/Characters/Conversations/Sentences/EventReactSentence.h"
#include "CastleLife/Tags/TagMapper.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Models/GameplayAbilityTargetData_SpeakingData.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "CastleLife/Tags/CastleLifeGameplayTags.h"
#include "CastleLife/Tags/TagCleaner.h"

USpeakToActor::USpeakToActor()
{
    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(TriggerTag);
    this->AbilityTriggers.Add(TriggerData);

    UTagMapper* TagMapper = NewObject<UTagMapper>() ;
    this->ActivationOwnedTags = TagMapper->ToTagContainer(OwnerTagsOnActivation);
    this->ActivationBlockedTags = TagMapper->ToTagContainer(OwnerBlockingTags);
}

void USpeakToActor::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo,
                                    const FGameplayEventData* TriggerEventData)
{
    ANpc_Character* CharacterSpeaking = Cast<ANpc_Character>(ActorInfo->OwnerActor);
    if (SpeakingZone == nullptr)
    {
        UTextRenderComponent* CharacterSpeakingZone = Cast<UTextRenderComponent>(
            CharacterSpeaking->FindComponentByClass(UTextRenderComponent::StaticClass()));
        SpeakingZone = CharacterSpeakingZone;
    }
    check(SpeakingZone != nullptr)
    
    FGameplayAbilityTargetDataHandle HandleData = TriggerEventData->TargetData;
    FGameplayAbilityTargetData* Data = HandleData.Get(0);
    
    checkf(Data != nullptr && Data->GetScriptStruct() == FGameplayAbilityTargetData_SpeakingData::StaticStruct(),
           TEXT("No speaking data, or wrong data type."))
    
    const FGameplayAbilityTargetData_SpeakingData* SpeakingData = StaticCast<FGameplayAbilityTargetData_SpeakingData*>(Data);
    LastSentenceTagName = SpeakingData->SentenceTagName;
    const FEventReactSentence Sentence = CharacterSpeaking->GetSpeakPhraseByTagName(LastSentenceTagName);
    SpeakingZone->SetText(FText::FromString(Sentence.Sentence));
    
    CurrentConversation = SpeakingData->Conversation == nullptr
                                      ? GetCharacterConversation(CharacterSpeaking)
                                      : SpeakingData->Conversation;
    
    CurrentConversation->AddProtagonist(CharacterSpeaking);
    CurrentConversation->AddAllProtagonists(SpeakingData->Receivers);
    CurrentConversation->NotifyOnCharacterStartSpeaking(SpeakingData->SentenceTagName, CharacterSpeaking, CurrentConversation);

    FGameplayTagContainer TagContainer;
    CharacterSpeaking->GetOwnedGameplayTags(TagContainer);

    EndAbility(Handle, ActorInfo, ActivationInfo, false, true);
}

void USpeakToActor::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                               bool bWasCancelled)
{
    check(CurrentConversation != nullptr)
    ACastleLifeCharacter* CharacterSpeaking = GetOwner(*ActorInfo);
    GetTagCleaner()->RemoveGameplayAbilityTags(CharacterSpeaking, OwnerTagsOnActivation);
    CurrentConversation->NotifyOnCharacterEndSpeaking(LastSentenceTagName, CharacterSpeaking, CurrentConversation);
}

UConversation* USpeakToActor::GetCharacterConversation(const ACastleLifeCharacter* Character) const
{
    AConversationManager* ConversationManager = nullptr;
    if (const UWorld* World = GetWorld())
    {
        TArray<AActor*> ConversationManagersFound;
        UGameplayStatics::GetAllActorsOfClass(World, AConversationManager::StaticClass(), ConversationManagersFound);
        check(ConversationManagersFound.Num() == 1)
        ConversationManager = Cast<AConversationManager>(ConversationManagersFound[0]);
    }
    check(ConversationManager != nullptr);

    UConversation* Conversation = ConversationManager->GetConversationByCharacter(Character);
    if (!Conversation)
    {
        Conversation = ConversationManager->CreateConversation();
    }

    return Conversation;
}

ACastleLifeCharacter* USpeakToActor::GetOwner(const FGameplayAbilityActorInfo& ActorInformation) const
{
    return Cast<ACastleLifeCharacter>(ActorInformation.OwnerActor);
}

ATagCleaner* USpeakToActor::GetTagCleaner()
{
    if(TagCleaner == nullptr)
    {
        UWorld* World = GetWorld();
        check(World != nullptr)

        TArray<AActor*> TagCleanersFound;
        UGameplayStatics::GetAllActorsWithTag(World, CastleLifeGameplayTags::Tag_Cleaner.GetTag().GetTagName(), TagCleanersFound);
        check(TagCleanersFound.Num() == 1);

        TagCleaner = Cast<ATagCleaner>(TagCleanersFound[0]);
    }
    check(TagCleaner != nullptr)
    return TagCleaner;
}


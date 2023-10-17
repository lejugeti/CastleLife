// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeakToActor.h"
#include "../Characters/Npc_Character.h"
#include "CastleLife/Characters/Conversations/Conversation.h"
#include "CastleLife/Characters/Conversations/ConversationManager.h"
#include "CastleLife/Characters/Conversations/Sentences/EventReactSentence.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Models/GameplayAbilityTargetData_SpeakingData.h"

USpeakToActor::USpeakToActor()
{
    checkf(TriggerTag.IsValid(), TEXT("Le tag de déclenchement de USpeakToActor doit être défini."))

    FAbilityTriggerData TriggerData;
    TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(TriggerTag);
    this->AbilityTriggers.Add(TriggerData);
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

    const FGameplayAbilityTargetData_SpeakingData* SpeakingData = StaticCast<FGameplayAbilityTargetData_SpeakingData
        *>(Data);
    const FEventReactSentence Sentence = CharacterSpeaking->GetSpeakPhraseByTagName(SpeakingData->SentenceTagName);
    SpeakingZone->SetText(FText::FromString(Sentence.Sentence));

    UConversation* Conversation = SpeakingData->Conversation == nullptr
                                      ? GetCharacterConversation(CharacterSpeaking)
                                      : SpeakingData->Conversation;
    
    Conversation->AddProtagonist(CharacterSpeaking);
    Conversation->AddAllProtagonists(SpeakingData->Receivers);
    Conversation->NotifyOnCharacterUseSentence(SpeakingData->SentenceTagName, CharacterSpeaking, Conversation);

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void USpeakToActor::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                               const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility,
                               bool bWasCancelled)
{
    // UE_LOG(LogTemp, Warning, TEXT("USpeakToActor end"));
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

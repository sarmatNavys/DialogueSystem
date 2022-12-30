// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSubsystem.h"

#include "DialogueFlowAsset.h"
#include "DialogueSystemPlugin.h"
#include "DialogueWidget.h"
#include "FlowSubsystem.h"
#include "Components/TextBlock.h"

UDialogueSubsystem::UDialogueSubsystem()
{
	CurrentDialogue = nullptr;
}

void UDialogueSubsystem::SetDialogueWidget(UDialogueWidget* NewDialogueWidget)
{
	check(NewDialogueWidget);
	
	DialogueWidget = NewDialogueWidget;
}

void UDialogueSubsystem::PhraseSaid() const
{
	DialogueWidget->DialogueLine->SetText(FText::GetEmpty());
	OnPhraseSaid.Broadcast();
}

void UDialogueSubsystem::StartDialogue(UDialogueFlowAsset* Dialogue)
{
	if (!Dialogue)
	{
		UE_LOG(LogDialogueSystemPlugin, Display, TEXT("Dialogue is null"));
		return;
	}
	
	CurrentDialogue = Dialogue;

	const UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	GameInstance->GetSubsystem<UFlowSubsystem>()->StartRootFlow(Dialogue, Dialogue, true);
	OnDialogueStarted.Broadcast(Dialogue);
}

void UDialogueSubsystem::StopDialogue()
{
	if (!CurrentDialogue)
	{
		UE_LOG(LogDialogueSystemPlugin, Display, TEXT("Cannot stop null dialogue"));
		return;
	}

	DialogueWidget->DialogueLine->SetText(FText::GetEmpty());

	const UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	GameInstance->GetSubsystem<UFlowSubsystem>()->FinishRootFlow(CurrentDialogue, EFlowFinishPolicy::Abort);
	OnDialogueEnded.Broadcast(CurrentDialogue);
}

void UDialogueSubsystem::AddDialoguePhrase(const FText& Phrase, const float& PhraseTime)
{
	//if (IsSayingPhrase()) return;

	DialogueWidget->DialogueLine->SetText(Phrase);
	GetWorld()->GetTimerManager().SetTimer(PhraseTimer, this, &UDialogueSubsystem::PhraseSaid, PhraseTime);
}

void UDialogueSubsystem::AddDialogueDecision(const TArray<FText>& Decisions)
{
	DialogueWidget->AddDecision(Decisions);
}

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
	//GetWorld()->GetTimerManager().ClearTimer(PhraseTimer);
	OnPhraseSaid.Broadcast();
}

void UDialogueSubsystem::StartDialogue(UDialogueFlowAsset* Dialogue, APlayerController* Player)
{
	if (!Dialogue)
	{
		UE_LOG(LogDialogueSystemPlugin, Display, TEXT("Dialogue is null"));
		return;
	}
	
	CurrentDialogue = Dialogue;

	FInputModeGameAndUI InputModeGameAndUI = FInputModeGameAndUI();
	InputModeGameAndUI.SetWidgetToFocus(DialogueWidget->TakeWidget());
	
	Player->SetInputMode(InputModeGameAndUI);
	Player->bShowMouseCursor = true;

	CurrentPlayerInDialogue = Player;
	
	const UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	GameInstance->GetSubsystem<UFlowSubsystem>()->StartRootFlow(Dialogue, Dialogue, true);
	OnDialogueStarted.Broadcast(Dialogue);
}

void UDialogueSubsystem::StopDialogue()
{
	if (!CurrentPlayerInDialogue) return;
	
	if (!CurrentDialogue)
	{
		UE_LOG(LogDialogueSystemPlugin, Display, TEXT("Cannot stop null dialogue"));
		return;
	}

	DialogueWidget->DialogueLine->SetText(FText::GetEmpty());

	CurrentPlayerInDialogue->SetInputMode(FInputModeGameOnly());
	CurrentPlayerInDialogue->bShowMouseCursor = false;
	
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

// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/FlowNode_AddPhrase.h"

#include "DialogueSubsystem.h"

UFlowNode_AddPhrase::UFlowNode_AddPhrase()
{
#if WITH_EDITOR
	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("Continue")));
	OutputPins.Add(FFlowPin(TEXT("Phrase Completed")));
#endif
}

void UFlowNode_AddPhrase::ExecuteInput(const FName& PinName)
{
	UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	
	DialogueSubsystem->AddDialoguePhrase(Phrase, PhraseTime);
	DialogueSubsystem->OnPhraseSaid.AddUniqueDynamic(this, &UFlowNode_AddPhrase::OnPhraseSaid);

	TriggerFirstOutput(true);
}

FString UFlowNode_AddPhrase::GetNodeDescription() const
{
	return "Add Phrase";
}

FText UFlowNode_AddPhrase::GetNodeTitle() const
{
	return FText::FromString("Add Dialogue Phrase");
}

FString UFlowNode_AddPhrase::GetNodeCategory() const
{
	return "Dialogue";
}

void UFlowNode_AddPhrase::OnPhraseSaid()
{
	UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	
	TriggerOutput(TEXT("Phrase Completed"), true);
	DialogueSubsystem->OnPhraseSaid.RemoveDynamic(this, &UFlowNode_AddPhrase::OnPhraseSaid);
}

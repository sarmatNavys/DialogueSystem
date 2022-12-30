// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/FlowNode_StopDialogue.h"

#include "DialogueFlowAsset.h"
#include "DialogueSubsystem.h"

void UFlowNode_StopDialogue::ExecuteInput(const FName& PinName)
{
	UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	DialogueSubsystem->StopDialogue();
	TriggerFirstOutput(true);
}

FString UFlowNode_StopDialogue::GetNodeDescription() const
{
	return "Stop Dialogue";
}

FText UFlowNode_StopDialogue::GetNodeTitle() const
{
	return FText::FromString("Stop Dialogue");
}

FString UFlowNode_StopDialogue::GetNodeCategory() const
{
	return "Dialogue";
}

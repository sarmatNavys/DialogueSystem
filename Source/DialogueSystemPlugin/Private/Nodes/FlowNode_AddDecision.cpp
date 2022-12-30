// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/FlowNode_AddDecision.h"

#include "DialogueSubsystem.h"

void UFlowNode_AddDecision::ExecuteInput(const FName& PinName)
{
	UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();

	DialogueSubsystem->AddDialogueDecision(Decisions);
	DialogueSubsystem->OnDecisionSelected.AddUniqueDynamic(this, &UFlowNode_AddDecision::OnDecisionSelected);
}

FString UFlowNode_AddDecision::GetNodeDescription() const
{
	return "Add Decision";
}

FText UFlowNode_AddDecision::GetNodeTitle() const
{
	return FText::FromString("Add Decision");
}

FString UFlowNode_AddDecision::GetNodeCategory() const
{
	return "Dialogue";
}

void UFlowNode_AddDecision::OnDecisionSelected(const int32& Index)
{
	UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();
	
	TriggerOutput(Decisions[Index], true);
	DialogueSubsystem->OnDecisionSelected.RemoveDynamic(this, &UFlowNode_AddDecision::OnDecisionSelected);
}

void UFlowNode_AddDecision::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UFlowNode_AddDecision, Decisions))
	{
		RefreshOutputPins();
		OnReconstructionRequested.ExecuteIfBound();
	}
	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UFlowNode_AddDecision::RefreshOutputPins()
{
	OutputPins.Empty();

	if (!Decisions.Num())
		OutputPins.Add(FFlowPin(TEXT("Continue")));

	for (auto Decision : Decisions)
	{
		OutputPins.Add(FFlowPin(Decision));
	}
}

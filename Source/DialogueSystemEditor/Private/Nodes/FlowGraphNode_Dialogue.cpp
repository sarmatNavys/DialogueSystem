// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/FlowGraphNode_Dialogue.h"

#include "Nodes/FlowNode_AddPhrase.h"
#include "Widgets/SFlowGraphNode_Dialogue.h"

UFlowGraphNode_Dialogue::UFlowGraphNode_Dialogue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AssignedNodeClasses = { UFlowNode_AddPhrase::StaticClass() };
}

TSharedPtr<SGraphNode> UFlowGraphNode_Dialogue::CreateVisualWidget()
{
	return SNew(SFlowGraphNode_Dialogue, this);
}

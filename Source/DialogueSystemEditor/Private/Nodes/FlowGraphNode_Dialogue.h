// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/Nodes/FlowGraphNode.h"
#include "FlowGraphNode_Dialogue.generated.h"

/**
 * 
 */
UCLASS()
class UFlowGraphNode_Dialogue : public UFlowGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
};

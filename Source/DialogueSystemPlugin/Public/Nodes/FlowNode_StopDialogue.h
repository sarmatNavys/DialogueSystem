// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_StopDialogue.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUGIN_API UFlowNode_StopDialogue : public UFlowNode
{
	GENERATED_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FText GetNodeTitle() const override;
	virtual FString GetNodeCategory() const override;
#endif
};

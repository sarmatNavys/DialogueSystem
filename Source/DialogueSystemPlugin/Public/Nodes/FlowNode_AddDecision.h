// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_AddDecision.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUGIN_API UFlowNode_AddDecision : public UFlowNode
{
	GENERATED_BODY()

protected:
	virtual void ExecuteInput(const FName& PinName) override;

	UPROPERTY(EditAnywhere)
	TArray<FText> Decisions;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void RefreshOutputPins();

	virtual FString GetNodeDescription() const override;
	virtual FText GetNodeTitle() const override;
	virtual FString GetNodeCategory() const override;
#endif

private:
	UFUNCTION()
	void OnDecisionSelected(const int32& Index);
};

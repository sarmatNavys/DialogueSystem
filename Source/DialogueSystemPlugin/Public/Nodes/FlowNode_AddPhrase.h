// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_AddPhrase.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUGIN_API UFlowNode_AddPhrase : public UFlowNode
{
	GENERATED_BODY()

protected:
	UFlowNode_AddPhrase();
	
	virtual void ExecuteInput(const FName& PinName) override;

	UPROPERTY(EditAnywhere)
	FText Phrase;

	UPROPERTY(EditAnywhere)
	float PhraseTime;

#if WITH_EDITOR
	virtual FString GetNodeDescription() const override;
	virtual FText GetNodeTitle() const override;
	virtual FString GetNodeCategory() const override;
#endif

private:
	UFUNCTION()
	void OnPhraseSaid();
};

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

public:
	FORCEINLINE FText GetPhrase() const { return Phrase; }
	FORCEINLINE FText GetSpeakerName() const { return SpeakerName; }
	FORCEINLINE FText GetPronounsText() const { return PronounsText; }
	FORCEINLINE FLinearColor GetSpeakerColor() const { return SpeakerColor; }
	FORCEINLINE FLinearColor GetPronounColor() const { return PronounColor; }
	
protected:
	UFlowNode_AddPhrase();
	
	virtual void ExecuteInput(const FName& PinName) override;

	UPROPERTY(EditAnywhere)
	FText Phrase;

	UPROPERTY(EditAnywhere)
	FText SpeakerName;

	UPROPERTY(EditAnywhere)
	FText PronounsText;

	UPROPERTY(EditAnywhere)
	FLinearColor SpeakerColor;

	UPROPERTY(EditAnywhere)
	FLinearColor PronounColor;

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

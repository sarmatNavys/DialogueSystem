// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DecisionWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecisionSelected, const int32&, Index);

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUGIN_API UDecisionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void SetDecision(const FText& Decision, const int32& InputDecisionIndex);
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DecisionText;

	UPROPERTY(meta = (BindWidget))
	class UButton* DecisionButton;

	UPROPERTY()
	FOnDecisionSelected OnDecisionSelected;

	int32 DecisionIndex;

private:
	UFUNCTION()
	void OnDecisionButtonClicked();
};

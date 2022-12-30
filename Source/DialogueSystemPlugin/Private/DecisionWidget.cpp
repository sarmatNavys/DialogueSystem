// Fill out your copyright notice in the Description page of Project Settings.


#include "DecisionWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UDecisionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DecisionButton->OnClicked.AddUniqueDynamic(this, &UDecisionWidget::OnDecisionButtonClicked);
}

void UDecisionWidget::SetDecision(const FText& Decision, const int32& InputDecisionIndex)
{
	DecisionText->SetText(Decision);
	this->DecisionIndex = InputDecisionIndex;
}

void UDecisionWidget::OnDecisionButtonClicked()
{
	OnDecisionSelected.Broadcast(DecisionIndex);
}
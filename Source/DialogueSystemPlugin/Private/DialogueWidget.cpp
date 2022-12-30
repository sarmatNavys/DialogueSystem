// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueWidget.h"

#include "DecisionWidget.h"
#include "DialogueSubsystem.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UDialogueWidget::NativeConstruct()
{
	Super::NativeConstruct();

	check(DialogueLine);
}

void UDialogueWidget::AddDecision(const TArray<FText>& Decisions)
{
	DecisionsBox->ClearChildren();

	for (int32 i = 0; i < Decisions.Num(); i++)
	{
		UDecisionWidget* DecisionWidget = CreateWidget<UDecisionWidget>(GetWorld(), DecisionWidgetClass);
		DecisionWidget->SetDecision(Decisions[i], i);
		DecisionWidget->OnDecisionSelected.AddUniqueDynamic(this, &UDialogueWidget::OnDecisionSelected);

		DecisionsBox->AddChild(DecisionWidget);
	}
}

void UDialogueWidget::OnDecisionSelected(const int32& Index)
{
	const UDialogueSubsystem* DialogueSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDialogueSubsystem>();

	DialogueLine->SetText(FText::GetEmpty());
	DecisionsBox->ClearChildren();
	DialogueSubsystem->OnDecisionSelected.Broadcast(Index);
}

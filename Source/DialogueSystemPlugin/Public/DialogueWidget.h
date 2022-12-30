// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMPLUGIN_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

friend class UDialogueSubsystem;
	
protected:
	virtual void NativeConstruct() override;
	
	/** Dialogue text, will appear when dialogue start and is valid */
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DialogueLine;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* DecisionsBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UDecisionWidget> DecisionWidgetClass;

	void AddDecision(const TArray<FText>& Decisions);

	UFUNCTION()
	void OnDecisionSelected(const int32& Index);
};

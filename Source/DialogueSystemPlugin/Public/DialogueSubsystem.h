// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueStarted, class UDialogueFlowAsset*, Dialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, class UDialogueFlowAsset*, Dialogue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecisionAccepted, const int32&, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPhraseSaid);

/**
 Major subsystem, controls all dialogue flow features 
 */
UCLASS(Blueprintable)
class DIALOGUESYSTEMPLUGIN_API UDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue Subsystem")
	void StartDialogue(UDialogueFlowAsset* Dialogue, APlayerController* Player);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Subsystem")
	void StopDialogue();

	UFUNCTION(BlueprintCallable, Category = "Dialogue Subsystem")
	void AddDialoguePhrase(const FText& Phrase, const float& PhraseTime);

	UFUNCTION(BlueprintCallable, Category = "Dialogue Subsystem")
	void AddDialogueDecision(const TArray<FText>& Decisions);

	UPROPERTY()
	FOnDecisionAccepted OnDecisionSelected;
	
	UPROPERTY(BlueprintReadOnly, Category = "Dialogue Sybsystem")
	class UDialogueFlowAsset* CurrentDialogue;

	UFUNCTION(BlueprintPure, Category = "Dialogue Subsystem")
	FORCEINLINE bool IsDialogueStarted() const { return bIsInDialogue; }

	UPROPERTY(BlueprintAssignable, Category = "Dialogue Subsystem")
	FOnDialogueStarted OnDialogueStarted;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue Subsystem")
	FOnDialogueEnded OnDialogueEnded;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue Subsystem")
	FOnPhraseSaid OnPhraseSaid;

	UFUNCTION(BlueprintCallable, Category = "Dialogue Subsystem")
	void SetDialogueWidget(class UDialogueWidget* NewDialogueWidget);

	UFUNCTION(BlueprintPure, Category = "Dialogue Subsystem")
	FORCEINLINE bool IsSayingPhrase() const { return GetWorld()->GetTimerManager().IsTimerActive(PhraseTimer); }
	
protected:
	UDialogueSubsystem();

	UPROPERTY()
	class UDialogueWidget* DialogueWidget;

	UPROPERTY()
	APlayerController* CurrentPlayerInDialogue;
	
	bool bIsInDialogue;

	FTimerHandle PhraseTimer;

	UFUNCTION()
	void PhraseSaid() const;
};

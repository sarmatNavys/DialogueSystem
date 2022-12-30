// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DialogueFlowAssetFactory.generated.h"

/**
 *
 */
UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueFlowAssetFactory : public UFactory
{
	GENERATED_BODY()

	UDialogueFlowAssetFactory();
	
protected:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual FText GetDisplayName() const override;
};

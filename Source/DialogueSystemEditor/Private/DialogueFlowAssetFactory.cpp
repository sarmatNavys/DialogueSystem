// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueFlowAssetFactory.h"

#include "DialogueFlowAsset.h"
#include "FlowEditor/Public/Graph/FlowGraph.h"

UDialogueFlowAssetFactory::UDialogueFlowAssetFactory()
{
	SupportedClass = UDialogueFlowAsset::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UDialogueFlowAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                     EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDialogueFlowAsset* DialogueFlowAsset = NewObject<UDialogueFlowAsset>(InParent, InClass, InName, Flags | RF_Transactional);
	UFlowGraph::CreateGraph(DialogueFlowAsset);
	
	return DialogueFlowAsset;
}

FText UDialogueFlowAssetFactory::GetDisplayName() const
{
	return FText::FromString("Dialogue Asset");
}

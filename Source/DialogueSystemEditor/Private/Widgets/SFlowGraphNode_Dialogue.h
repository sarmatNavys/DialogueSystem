// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/Widgets/SFlowGraphNode.h"

/**
 * 
 */
class DIALOGUESYSTEMEDITOR_API SFlowGraphNode_Dialogue : public SFlowGraphNode
{

protected:
	virtual void UpdateGraphNode() override;

	virtual TSharedRef<SWidget> CreateDialogueContentArea();
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;

	virtual TSharedRef<SWidget> CreateTitleBar();
	
public:
	SLATE_BEGIN_ARGS(SFlowGraphNode_Dialogue) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, UFlowGraphNode* InNode);

	TSharedPtr<SVerticalBox> TitleBox;
	TSharedPtr<SHorizontalBox> TitleBoxH;

	FSlateBrush Brush;

	FSlateColor SpeakerTextColor;
	FSlateColor PronounTextColor;

	FSlateColor SpeakerBgColor;
	FSlateBrush SpeakerBgBrush;
	FSlateBrush SpeakerBgCornerBrush;

	FSlateColor PronounBgColor;
	FSlateBrush PronounBgBrush;
	FSlateBrush PronounBgCornerBrush;
};

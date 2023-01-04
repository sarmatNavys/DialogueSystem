// Fill out your copyright notice in the Description page of Project Settings.


#include "SFlowGraphNode_Dialogue.h"

#include "FlowEditorStyle.h"
#include "GraphEditorSettings.h"
#include "SCommentBubble.h"
#include "SlateOptMacros.h"
#include "TutorialMetaData.h"
#include "Graph/FlowGraphEditorSettings.h"
#include "Nodes/FlowNode.h"
#include "Nodes/FlowNode_AddPhrase.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#define LOCTEXT_NAMESPACE "DialogueFlowEditor"

void SFlowGraphNode_Dialogue::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SVerticalBox> MainVerticalBox;
	SetupErrorReporting();

	const TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	IconColor = FLinearColor::White;
	const FSlateBrush* IconBrush = nullptr;
	if (GraphNode && GraphNode->ShowPaletteIconOnNode())
	{
		IconBrush = GraphNode->GetIconAndTint(IconColor).GetOptionalIcon();
	}

	const TSharedRef<SOverlay> DefaultTitleAreaWidget = SNew(SOverlay)
		+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Fill)
					[
						SNew(SBorder)
							.BorderImage(FFlowEditorStyle::GetBrush("Flow.Node.Title"))
							.Padding(FMargin(10, 5, 30, 3))
							.BorderBackgroundColor(this, &SGraphNode::GetNodeTitleColor)
							[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
									.VAlign(VAlign_Top)
									.Padding(FMargin(0.f, 0.f, 4.f, 0.f))
									.AutoWidth()
									[
										SNew(SImage)
											.Image(IconBrush)
											.ColorAndOpacity(this, &SGraphNode::GetNodeTitleIconColor)
									]
								+ SHorizontalBox::Slot()
									[
										SNew(SVerticalBox)
										+ SVerticalBox::Slot()
											.AutoHeight()
											[
												CreateTitleWidget(NodeTitle)
											]
										+ SVerticalBox::Slot()
											.AutoHeight()
											[
												NodeTitle.ToSharedRef()
											]
									]
							]
					]
			];

	FGraphNodeMetaData TagMeta(TEXT("FlowGraphNode"));
	PopulateMetaTag(&TagMeta);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	const TSharedPtr<SVerticalBox> InnerVerticalBox = SNew(SVerticalBox)
		+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			[
				CreateNodeContentArea()
			];

	const TSharedPtr<SWidget> EnabledStateWidget = GetEnabledStateWidget();
	if (EnabledStateWidget.IsValid())
	{
		InnerVerticalBox->AddSlot()
			.AutoHeight()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Top)
			.Padding(FMargin(2, 0))
			[
				EnabledStateWidget.ToSharedRef()
			];
	}

	InnerVerticalBox->AddSlot()
		.AutoHeight()
		.Padding(Settings->GetNonPinNodeBodyPadding())
		[
			ErrorReporting->AsWidget()
		];

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SAssignNew(MainVerticalBox, SVerticalBox)
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoHeight()
				[
					CreateTitleBar()
				]
			+ SVerticalBox::Slot()
				.HAlign(HAlign_Fill)
				.AutoHeight()
				[
					SNew(SOverlay)
						.AddMetaData<FGraphNodeMetaData>(TagMeta)
						+ SOverlay::Slot()
							.Padding(Settings->GetNonPinNodeBodyPadding())
							[
								SNew(SImage)
									.Image(GetNodeBodyBrush())
									.ColorAndOpacity(this, &SGraphNode::GetNodeBodyColor)
							]
						+ SOverlay::Slot()
							[
								InnerVerticalBox.ToSharedRef()
							]
				]
		];

	if (GraphNode && GraphNode->SupportsCommentBubble())
	{
		TSharedPtr<SCommentBubble> CommentBubble;
		const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

		SAssignNew(CommentBubble, SCommentBubble)
			.GraphNode(GraphNode)
			.Text(this, &SGraphNode::GetNodeComment)
			.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
			.OnToggled(this, &SGraphNode::OnCommentBubbleToggled)
			.ColorAndOpacity(CommentColor)
			.AllowPinning(true)
			.EnableTitleBarBubble(true)
			.EnableBubbleCtrls(true)
			.GraphLOD(this, &SGraphNode::GetCurrentLOD)
			.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

		GetOrAddSlot(ENodeZone::TopCenter)
			.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
			.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
			.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
			.VAlign(VAlign_Top)
			[
				CommentBubble.ToSharedRef()
			];
	}

	CreateBelowWidgetControls(MainVerticalBox);
	CreatePinWidgets();
	CreateInputSideAddButton(LeftNodeBox);
	CreateOutputSideAddButton(RightNodeBox);
	CreateBelowPinControls(InnerVerticalBox);
	CreateAdvancedViewArrow(InnerVerticalBox);
}

TSharedRef<SWidget> SFlowGraphNode_Dialogue::CreateDialogueContentArea()
{
	if (UFlowNode* FlowNode = FlowGraphNode->GetFlowNode())
	{
		const UFlowNode_AddPhrase* DialogueNode = Cast<UFlowNode_AddPhrase>(FlowNode);
		//bool UseImage = false;
		//Brush.ImageSize = FVector2D(64, 64);

		if (DialogueNode)
		{
			const FText DialogueText = DialogueNode->GetPhrase();

			return SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.Padding(10.f)
				[
					SNew(STextBlock)
					.Text(DialogueText)
					.WrapTextAt(250.f)
				];
		}	
	}

	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.Padding(10.f)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("Broken node", "This node seems to be broken. Please recreate it!"))
			.WrapTextAt(370.f)
		];
}

TSharedRef<SWidget> SFlowGraphNode_Dialogue::CreateNodeContentArea()
{
	return SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("NoBorder"))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.FillWidth(1.0f)
			[
				CreateDialogueContentArea()
			]
			+ SHorizontalBox::Slot()
			.AutoWidth()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			[
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		];
}

void SFlowGraphNode_Dialogue::CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox)
{
	if (UFlowNode* FlowNode = FlowGraphNode->GetFlowNode())
	{
		const UFlowNode_AddPhrase* DialogueNode = Cast<UFlowNode_AddPhrase>(FlowNode);
		if (DialogueNode)
		{
			const FText DialogueText = DialogueNode->GetPhrase();

			MainBox->AddSlot()
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.FillWidth(1.0f)
				.Padding(10.f)
					[
						SNew(STextBlock)
						.Text(DialogueText)
						.WrapTextAt(250.f)
					]
			];
		}
	}
}

TSharedRef<SWidget> SFlowGraphNode_Dialogue::CreateTitleBar()
{
	FText NodeTitleText =  LOCTEXT("Invalid Speaker", "Invalid Speaker!");
	FText NodeTitlePronouns;
	FLinearColor SpeakerColor;
	FLinearColor PronounColor;
	if (UFlowNode* FlowNode = FlowGraphNode->GetFlowNode())
	{
		const UFlowNode_AddPhrase* DialogueNode = Cast<UFlowNode_AddPhrase>(FlowNode);
		NodeTitleText = DialogueNode->GetSpeakerName();
		NodeTitlePronouns = DialogueNode->GetPronounsText();
		SpeakerColor = DialogueNode->GetSpeakerColor();
		PronounColor = DialogueNode->GetPronounColor();
	}

	SpeakerBgBrush.TintColor = SpeakerColor;
	SpeakerBgCornerBrush.TintColor = SpeakerColor;
	PronounBgBrush.TintColor = PronounColor;
	PronounBgCornerBrush.TintColor = PronounColor;

	SAssignNew(TitleBoxH, SHorizontalBox)
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.Padding(10.f, 0.f, 0.f, 0.f)
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(&SpeakerBgBrush)
		.Padding(FMargin(10.f, 4.f))
		.VAlign(VAlign_Fill)
		[
			SAssignNew(InlineEditableText, SInlineEditableTextBlock)
				.Style(FEditorStyle::Get(), "Graph.Node.NodeTitleInlineEditableText")
				.Text(NodeTitleText)
				.ColorAndOpacity(SpeakerTextColor)
				.IsReadOnly(true)
				.IsSelected(this, &SFlowGraphNode_Dialogue::IsSelectedExclusively)
		]
	]
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(&PronounBgBrush)
		.Padding(0.f)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderImage(&SpeakerBgCornerBrush)
			.Padding(FMargin(10.f, 0.f))
			.VAlign(VAlign_Fill)
		]
	]
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(&PronounBgBrush)
		.Padding(FMargin(10.f, 4.f))
		.VAlign(VAlign_Fill)
		[
			SNew(STextBlock)
			.Text(NodeTitlePronouns)
			.ColorAndOpacity(PronounTextColor)
		]
	]
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(&PronounBgCornerBrush)
		.Padding(FMargin(10.f, 0.f))
		.VAlign(VAlign_Fill)
	];

	return TitleBoxH.ToSharedRef();
}

void SFlowGraphNode_Dialogue::Construct(const FArguments& InArgs, UFlowGraphNode* InNode)
{
	SpeakerTextColor = FLinearColor(0.f, 0.f, 0.f, 1.f);
	PronounTextColor = FLinearColor(1.f, 1.f, 1.f, 1.f);

	GraphNode = InNode;
	FlowGraphNode = InNode;

	SetCursor(EMouseCursor::CardinalCross);
	UpdateGraphNode();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

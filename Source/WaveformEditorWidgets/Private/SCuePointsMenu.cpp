#include "WaveformEditorWidgets/Public/SCuePointsMenu.h"

#include "Runtime/Slate/Private/Widgets/Views/SListPanel.h"

void SCuePointsMenu::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString SCuePointsMenu::GetReferencerName() const
{
	return TEXT("SCuePointsMenu");
}

void SCuePointsMenu::Construct(const FArguments& InArgs)
{
	this->SoundWaveAsset = InArgs._SoundWaveAsset;
	TSharedPtr<SListPanel> CuePointList = SNew(SListPanel)
		+SListPanel::Slot()
		[
			SNew(SHeaderRow)
			+SHeaderRow::Column("Header")
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("Header")))
			]
		];

	for (const auto& cuePoint : SoundWaveAsset->CuePoints)
	{
		FText cuePointId = FText::FromString(FString::FromInt(cuePoint.CuePointID));
		FText label = FText::FromString(cuePoint.Label);
		FText framePosition = FText::FromString(FString::FromInt(cuePoint.FramePosition));
		FText frameLength = FText::FromString(FString::FromInt(cuePoint.FrameLength));
		
		auto addSlot = [&CuePointList](FText name, FText value)
		{
			CuePointList->AddSlot()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(name)
				]
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(value)
				]
			];
		};

		addSlot(FText::FromString("cuePointId"), cuePointId);
		addSlot(FText::FromString("label"), label);
		addSlot(FText::FromString("framePosition"), framePosition);
		addSlot(FText::FromString("frameLength"), frameLength);
	}
	
	this->ChildSlot
	[
		CuePointList.ToSharedRef()
	];
}

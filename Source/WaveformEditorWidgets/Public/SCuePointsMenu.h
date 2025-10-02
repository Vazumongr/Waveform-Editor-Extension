#pragma once

class WAVEFORMEDITORWIDGETS_API SCuePointsMenu : public SCompoundWidget, public FGCObject
{
	SLATE_BEGIN_ARGS(SCuePointsMenu)
		{ }

		SLATE_ARGUMENT(USoundWave*, SoundWaveAsset)
		
	SLATE_END_ARGS()

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;

	void Construct(const FArguments& InArgs);


	USoundWave* SoundWaveAsset;
};
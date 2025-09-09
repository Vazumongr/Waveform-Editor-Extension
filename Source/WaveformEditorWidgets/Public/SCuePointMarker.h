#pragma once

#include "Widgets/SLeafWidget.h"

class WAVEFORMEDITORWIDGETS_API SCuePointMarker : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SCuePointMarker)
	{}

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, FSoundWaveCuePoint InCuePoint);

	void SetMarkerPosition(const float InNewPosition);
	float GetMarkerPosition() const { return MarkerPosition; }

	FSoundWaveCuePoint GetCuePoint() const { return CuePoint; }

private:
	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	int32 DrawPlayhead(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements, int32 LayerId) const;

	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;

	FSlateColor MarkerColor = FLinearColor(0.f, 255.f, 0.f, 1.f);
	float MarkerWidth = 1.0;
	float DesiredWidth = 0.f;
	float DesiredHeight = 0.f;

	float MarkerPosition = 0.f;

	FSoundWaveCuePoint CuePoint;
};
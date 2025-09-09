#include "SCuePointMarker.h"

void SCuePointMarker::Construct(const FArguments& InArgs, FSoundWaveCuePoint InCuePoint)
{
	CuePoint = InCuePoint;
}

void SCuePointMarker::SetMarkerPosition(const float InNewPosition)
{
	MarkerPosition = InNewPosition;
}

int32 SCuePointMarker::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
							   const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
							   const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	LayerId = DrawPlayhead(AllottedGeometry, OutDrawElements, LayerId);

	return LayerId;
}

int32 SCuePointMarker::DrawPlayhead(const FGeometry& AllottedGeometry, FSlateWindowElementList& OutDrawElements,
	int32 LayerId) const
{
	const float MarkerX = MarkerPosition;

	TArray<FVector2D> LinePoints{ FVector2D(MarkerX, 0.0f), FVector2D(MarkerX, AllottedGeometry.Size.Y)};

	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		LinePoints,
		ESlateDrawEffect::None,
		MarkerColor.GetSpecifiedColor(),
		true,
		MarkerWidth
	);

	return ++LayerId;
}

FVector2D SCuePointMarker::ComputeDesiredSize(float LayoutScaleMultiplier) const
{
	return FVector2D(DesiredWidth, DesiredHeight);
}

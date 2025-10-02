// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "AudioWidgetsSlateTypes.h"
#include "HAL/Platform.h"
#include "Widgets/SCompoundWidget.h"
#include "IFixedSampledSequenceViewReceiver.h"

class SExtendedFixedSampleSequenceRuler;
class SCuePointMarker;
enum class ESampledSequenceDisplayUnit;
struct FNotifyingAudioWidgetStyle;

class FSparseSampledSequenceTransportCoordinator;
class FWaveformEditorGridData;
class FWaveformEditorRenderData;
class FWaveformEditorStyle;
class FWaveformEditorZoomController;
class SBorder;
class SFixedSampledSequenceRuler;
class SFixedSampledSequenceViewer;
class SPlayheadOverlay;
class SSampledSequenceValueGridOverlay;
class SWaveformEditorInputRoutingOverlay;
class SWaveformTransformationsOverlay;
class UWaveformEditorWidgetsSettings;

class WAVEFORMEDITORWIDGETS_API STransformedWaveformViewPanel : public SCompoundWidget, public IFixedSampledSequenceViewReceiver 
{
public: 
	SLATE_BEGIN_ARGS(STransformedWaveformViewPanel) {}
		
		SLATE_DEFAULT_SLOT(FArguments, InArgs)
		
		SLATE_ARGUMENT(TSharedPtr<SWaveformTransformationsOverlay>, TransformationsOverlay)

		SLATE_ARGUMENT(FPointerEventHandler, OnPlayheadOverlayMouseButtonUp)

		SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseButtonUp)

		SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseButtonDown)

		SLATE_ARGUMENT(FPointerEventHandler, OnTimeRulerMouseMove)

		SLATE_ARGUMENT(FPointerEventHandler, OnMouseWheel)

	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs, const FFixedSampledSequenceView& InView, const TArray<FSoundWaveCuePoint>& InCuePoints, TObjectPtr<USoundWave> InSoundWave);
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual void ReceiveSequenceView(const FFixedSampledSequenceView InView, const uint32 FirstSampleIndex = 0) override;
	void SetPlayheadRatio(const float InRatio);

	void SetOnPlayheadOverlayMouseButtonUp(FPointerEventHandler InEventHandler);
	void SetOnTimeRulerMouseButtonUp(FPointerEventHandler InEventHandler);
	void SetOnTimeRulerMouseButtonDown(FPointerEventHandler InEventHandler);
	void SetOnTimeRulerMouseMove(FPointerEventHandler InEventHandler);
	void SetOnMouseWheel(FPointerEventHandler InEventHandler);

	FReply LaunchTimeRulerContextMenu();

	void UpdateCuePoints();

private:
	void CreateLayout();

	void SetUpGridData();
	void SetupPlayheadOverlay();
	void SetupCuePointMarkers();
	void SetUpTimeRuler(TSharedRef<FWaveformEditorGridData> InGridData);
	void SetUpWaveformViewer(TSharedRef<FWaveformEditorGridData> InGridData, const FFixedSampledSequenceView& InView);
	void SetUpInputRoutingOverlay();
	void SetUpInputOverrides(const FArguments& InArgs);
	void SetUpValueGridOverlay();
	void SetUpBackground();


	void UpdateDisplayUnit(const ESampledSequenceDisplayUnit InDisplayUnit);
	void UpdatePlayheadPosition(const float PaintedWidth);
	void UpdateCuePointMarkerPositions(const float PaintedWidth);
	void UpdateBackground(const FSampledSequenceViewerStyle UpdatedStyle);

	void OnWaveEditorWidgetSettingsUpdated(const FName& PropertyName, const UWaveformEditorWidgetsSettings* Settings);

	TSharedPtr<FWaveformEditorGridData> GridData;

	TSharedPtr<SExtendedFixedSampleSequenceRuler> TimeRuler;
	TSharedPtr<SFixedSampledSequenceViewer> WaveformViewer;
 	TSharedPtr<SWaveformTransformationsOverlay> WaveformTransformationsOverlay;
	TSharedPtr<SWaveformEditorInputRoutingOverlay> InputRoutingOverlay;
	TSharedPtr<SPlayheadOverlay> PlayheadOverlay;
	TSharedPtr<SSampledSequenceValueGridOverlay> ValueGridOverlay;
	TSharedPtr<SBorder> BackgroundBorder;
	TSharedPtr<SOverlay> CuePointMarkerOverlay;
	TSharedPtr<SOverlay> WaveformView;

	TArray<TSharedPtr<SCuePointMarker>> CuePointMarkers;
	TWeakObjectPtr<USoundWave> SoundWaveToDisplay;
	TArray<FSoundWaveCuePoint> CuePoints;

	float CachedPixelWidth = 0.f;

	ESampledSequenceDisplayUnit DisplayUnit;

	FWaveformEditorStyle* WaveformEditorStyle;

	FFixedSampledSequenceView DataView;
	
	float CachedPlayheadRatio = 0.f;
	const UWaveformEditorWidgetsSettings* GetWaveformEditorWidgetsSettings();
};
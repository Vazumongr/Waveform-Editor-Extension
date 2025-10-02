// Copyright Troy Records Jr. 2025


#include "WaveformEditorCuePointProxy.h"
#include "Sound/SoundWave.h"

#include "WaveformEditorLog.h"

FSoundWaveCuePointProxy::FSoundWaveCuePointProxy(FSoundWaveCuePoint CuePoint)
{
	CuePointID = CuePoint.CuePointID;
	Label = CuePoint.Label;
	FramePosition = CuePoint.FramePosition;
	FrameLength = CuePoint.FrameLength;
}

FSoundWaveCuePoint FSoundWaveCuePointProxy::GetAsCuePoint() const
{
	FSoundWaveCuePoint cuePoint;
	cuePoint.CuePointID = CuePointID;
	cuePoint.Label = Label;
	cuePoint.FramePosition = FramePosition;
	cuePoint.FrameLength = FrameLength;
	return cuePoint;
}

void UWaveformEditorCuePointProxyContainer::Initialize(USoundWave* InSoundWave)
{
	if (InSoundWave == nullptr)
	{
		UE_LOG(LogWaveformEditorExtension, Warning, TEXT("Trying to initialize CuePointProxyContainer with a nullptr SoundWave"));
		return;
	}
	for (const auto& cuePoint : InSoundWave->CuePoints)
	{
		CuePointProxies.Emplace(cuePoint);
	}
	SoundWave = InSoundWave;
}

void UWaveformEditorCuePointProxyContainer::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);
	UpdateSourceCuePoints();
}

void UWaveformEditorCuePointProxyContainer::UpdateSourceCuePoints()
{
	if (SoundWave != nullptr)
	{
		SoundWave->CuePoints = GetConvertedProxies();
	}
	OnDataUpdated.Broadcast();
}

void UWaveformEditorCuePointProxyContainer::AddCuePoint(FSoundWaveCuePoint InCuePoint)
{
	CuePointProxies.Emplace(InCuePoint);
	UpdateSourceCuePoints();
}

TArray<FSoundWaveCuePoint> UWaveformEditorCuePointProxyContainer::GetConvertedProxies() const
{
	TArray<FSoundWaveCuePoint> cuePoints;
	for (const auto& proxy : CuePointProxies)
	{
		cuePoints.Add(proxy.GetAsCuePoint());
	}
	return cuePoints;
}

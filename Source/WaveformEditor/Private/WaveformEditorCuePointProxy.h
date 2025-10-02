// Copyright Troy Records Jr. 2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WaveformEditorCuePointProxy.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDataUpdated);

/**
 * 
 */
USTRUCT()
struct FSoundWaveCuePointProxy
{
	GENERATED_BODY()
public:
	FSoundWaveCuePointProxy() = default;
	FSoundWaveCuePointProxy(FSoundWaveCuePoint CuePoint);

	FSoundWaveCuePoint GetAsCuePoint() const;
	
	// Unique identifier for the wave cue point
	UPROPERTY(Category = Info, EditAnywhere)
	int32 CuePointID = 0;

	// The label for the cue point
	UPROPERTY(Category = Info, EditAnywhere)
	FString Label;

	// The frame position of the cue point
	UPROPERTY(Category = Info, EditAnywhere)
	int32 FramePosition = 0;

	// The frame length of the cue point (non-zero if it's a region)
	UPROPERTY(Category = Info, EditAnywhere)
	int32 FrameLength = 0;
};

UCLASS()
class WAVEFORMEDITOR_API UWaveformEditorCuePointProxyContainer : public UObject
{
	GENERATED_BODY()
public:
	void Initialize(USoundWave* InSoundWave);

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	void UpdateSourceCuePoints();

	void AddCuePoint(FSoundWaveCuePoint InCuePoint);

	FOnDataUpdated OnDataUpdated;
private:

	TArray<FSoundWaveCuePoint> GetConvertedProxies() const;
	
	UPROPERTY(EditAnywhere)
	TArray<FSoundWaveCuePointProxy> CuePointProxies;

	UPROPERTY()
	USoundWave* SoundWave;
};
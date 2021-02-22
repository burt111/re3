#pragma once

#include "audio_enums.h"
#include "AudioCollision.h"
#include "PoliceRadio.h"
#include "VehicleModelInfo.h"
#include "Vehicle.h"

class tSound
{
public:
	int32 m_nEntityIndex;
	int32 m_nCounter;
	int32 m_nSampleIndex;
	uint8 m_nBankIndex;
	bool m_bIs2D;
	int32 m_nReleasingVolumeModificator;
	uint32 m_nFrequency;
	uint8 m_nVolume;
	float m_fDistance;
	int32 m_nLoopCount;
	int32 m_nLoopStart;
	int32 m_nLoopEnd;
	uint8 m_nEmittingVolume;
	float m_fSpeedMultiplier;
	float m_fSoundIntensity;
	bool m_bReleasingSoundFlag;
	CVector m_vecPos;
	bool m_bReverbFlag;
	uint8 m_nLoopsRemaining;
	bool m_bRequireReflection; // Used for oneshots
	uint8 m_nOffset;
	uint8 field_4C;
	int32 m_nReleasingVolumeDivider;
	bool m_bIsProcessed;
	bool m_bLoopEnded;
	int32 m_nCalculatedVolume;
	int8 m_nVolumeChange;
};

VALIDATE_SIZE(tSound, 96);

class CPhysical;
class CAutomobile;

class tAudioEntity
{
public:
	eAudioType m_nType;
	void *m_pEntity;
	bool m_bIsUsed;
	uint8 m_bStatus;
	int16 m_awAudioEvent[NUM_AUDIOENTITY_EVENTS];
	float m_afVolume[NUM_AUDIOENTITY_EVENTS];
	uint8 m_AudioEvents;
};

VALIDATE_SIZE(tAudioEntity, 40);

class tPedComment
{
public:
	uint32 m_nSampleIndex;
	int32 m_nEntityIndex;
	CVector m_vecPos;
	float m_fDistance;
	uint8 m_bVolume;
	int8 m_nProcess;
};

VALIDATE_SIZE(tPedComment, 28);

class cPedComments
{
public:
	tPedComment m_asPedComments[NUM_PED_COMMENTS_BANKS][NUM_PED_COMMENTS_SLOTS];
	uint8 m_nIndexMap[NUM_PED_COMMENTS_BANKS][NUM_PED_COMMENTS_SLOTS];
	uint8 m_nCommentsInBank[NUM_PED_COMMENTS_BANKS];
	uint8 m_nActiveBank;
#ifdef GTA_PC
	bool m_bDelay;
	uint32 m_nDelayTimer;
#endif

	cPedComments()
	{
		for (int i = 0; i < NUM_PED_COMMENTS_SLOTS; i++)
			for (int j = 0; j < NUM_PED_COMMENTS_BANKS; j++) {
				m_asPedComments[j][i].m_nProcess = -1;
				m_nIndexMap[j][i] = NUM_PED_COMMENTS_SLOTS;
			}

		for (int i = 0; i < NUM_PED_COMMENTS_BANKS; i++)
			m_nCommentsInBank[i] = 0;
		m_nActiveBank = 0;
	}
	void Add(tPedComment *com); // done
	void Process();             // done
};

VALIDATE_SIZE(cPedComments, 0x490);

class CEntity;

#define MISSION_AUDIO_SLOTS (2)

// So instead of doing cMissionAudio [2] they've added [2] to every field of the struct...
// Only someone with a VERY EXTRAORDINARY mind could have come up with that
class cMissionAudio
{
public:
	CVector m_vecPos[MISSION_AUDIO_SLOTS];
	bool m_bPredefinedProperties[MISSION_AUDIO_SLOTS];
	int32 m_nSampleIndex[MISSION_AUDIO_SLOTS];
	uint8 m_nLoadingStatus[MISSION_AUDIO_SLOTS];
	uint8 m_nPlayStatus[MISSION_AUDIO_SLOTS];
	bool m_bIsPlaying[MISSION_AUDIO_SLOTS];
	int32 m_nMissionAudioCounter[MISSION_AUDIO_SLOTS];
	bool m_bIsPlayed[MISSION_AUDIO_SLOTS];
	bool m_bIsMobile[MISSION_AUDIO_SLOTS];
};
VALIDATE_SIZE(cMissionAudio, 0x38);

// name made up
class cAudioScriptObjectManager
{
public:
	int32 m_anScriptObjectEntityIndices[NUM_SCRIPT_MAX_ENTITIES];
	int32 m_nScriptObjectEntityTotal;

	cAudioScriptObjectManager() { m_nScriptObjectEntityTotal = 0; }
	~cAudioScriptObjectManager() { m_nScriptObjectEntityTotal = 0; }
};


class cTransmission;
class CPlane;
class CVehicle;
class CPed;

class cPedParams
{
public:
	bool m_bDistanceCalculated;
	float m_fDistance;
	CPed *m_pPed;

	cPedParams()
	{
		m_bDistanceCalculated = false;
		m_fDistance = 0.0f;
		m_pPed = nil;
	}
};

class cVehicleParams
{
public:
	int32 m_VehicleType;
	bool m_bDistanceCalculated;
	float m_fDistance;
	CVehicle *m_pVehicle;
	cTransmission *m_pTransmission;
	int32 m_nIndex;
	float m_fVelocityChange;

	cVehicleParams()
	{
		m_VehicleType = -1;
		m_bDistanceCalculated = false;
		m_fDistance = 0.0f;
		m_pVehicle = nil;
		m_pTransmission = nil;
		m_nIndex = 0;
		m_fVelocityChange = 0.0f;
	}
};

VALIDATE_SIZE(cVehicleParams, 0x1C);

enum {
	REFLECTION_NORTH = 0,
	REFLECTION_SOUTH,
	REFLECTION_WEST,
	REFLECTION_EAST,
	REFLECTION_CEIL_NORTH,
	REFLECTION_CEIL_SOUTH,
	REFLECTION_CEIL_WEST,
	REFLECTION_CEIL_EAST,
	MAX_REFLECTIONS,
};

class cAudioManager
{
public:
	bool m_bIsInitialised;
	uint8 m_bReverb; // unused
	bool m_bFifthFrameFlag;
	uint8 m_nActiveSamples;
	uint8 field_4; // unused
	bool m_bDynamicAcousticModelingStatus;
	int8 field_6;
	float m_fSpeedOfSound;
	bool m_bTimerJustReset;
	int32 m_nTimer;
	tSound m_sQueueSample;
	uint8 m_nActiveSampleQueue;
	tSound m_asSamples[NUM_SOUNDS_SAMPLES_BANKS][NUM_SOUNDS_SAMPLES_SLOTS];
	uint8 m_abSampleQueueIndexTable[NUM_SOUNDS_SAMPLES_BANKS][NUM_SOUNDS_SAMPLES_SLOTS];
	uint8 m_SampleRequestQueuesStatus[NUM_SOUNDS_SAMPLES_BANKS];
	tSound m_asActiveSamples[NUM_SOUNDS_SAMPLES_SLOTS];
	tAudioEntity m_asAudioEntities[NUM_AUDIOENTITIES];
	int32 m_anAudioEntityIndices[NUM_AUDIOENTITIES];
	int32 m_nAudioEntitiesTotal;
	CVector m_avecReflectionsPos[NUM_AUDIO_REFLECTIONS];
	float m_afReflectionsDistances[NUM_AUDIO_REFLECTIONS];
	cAudioScriptObjectManager m_sAudioScriptObjectManager;

	// miami
	uint8 m_bIsPlayerShutUp;
	uint8 m_nPlayerMood;
	uint32 m_nPlayerMoodTimer;
	uint8 field_rest[4];
	bool m_bGenericSfx;

	cPedComments m_sPedComments;
	int32 m_nFireAudioEntity;
	int32 m_nWaterCannonEntity;
	int32 m_nPoliceChannelEntity;
	cPoliceRadioQueue m_sPoliceRadioQueue;
	int32 m_nFrontEndEntity;
	int32 m_nCollisionEntity;
	cAudioCollisionManager m_sCollisionManager;
	int32 m_nProjectileEntity;
#ifdef GTA_BRIDGE
	int32 m_nBridgeEntity;
#endif
	int32 m_nEscalatorEntity;
	int32 m_nExtraSoundsEntity;
	cMissionAudio m_sMissionAudio;
	uint8 field_5538; // something related to phone dialogues
	int32 m_anRandomTable[5];
	uint8 m_nTimeSpent;
	uint8 m_nUserPause;
	uint8 m_nPreviousUserPause;
	uint32 m_FrameCounter;

	cAudioManager();
	~cAudioManager();

	// getters
	uint32 GetFrameCounter() const { return m_FrameCounter; } // done
	float GetReflectionsDistance(int32 idx) const { return m_afReflectionsDistances[idx]; } // done
	int32 GetRandomNumber(int32 idx) const { return m_anRandomTable[idx]; }
	int32 GetRandomNumberInRange(int32 idx, int32 low, int32 high) const { return (m_anRandomTable[idx] % (high - low + 1)) + low; }
	bool IsMissionAudioSamplePlaying(uint8 slot) const; // { return m_sMissionAudio.m_nPlayStatus == 1; }
	bool ShouldDuckMissionAudio(uint8 slot) const;

	// "Should" be in alphabetic order, except "getXTalkSfx"
	void AddDetailsToRequestedOrderList(uint8 sample);                                                                    // done (inlined in vc)
	void AddPlayerCarSample(uint8 emittingVolume, int32 freq, uint32 sample, uint8 bank, uint8 counter, bool notLooping); // done
	v
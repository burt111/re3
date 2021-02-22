#include "common.h"

#include "Stats.h"
#include "Text.h"
#include "World.h"
#include "Pad.h"
#include "DMAudio.h"
#include "main.h"
#include "Font.h"
#include "Frontend.h"
#include "audio_enums.h"

#include <climits>

#ifdef USE_PRECISE_MEASUREMENT_CONVERTION
#define MILES_IN_METER 0.000621371192f
#define FEET_IN_METER 3.28084f
#else
#define MILES_IN_METER (1 / 1670.f)
#define FEET_IN_METER 3.33f
#endif

int32 CStats::SeagullsKilled;
int32 CStats::BoatsExploded;
int32 CStats::WantedStarsAttained;
int32 CStats::WantedStarsEvaded;
int32 CStats::DaysPassed;
int32 CStats::HeadsPopped;
int32 CStats::CommercialPassed;
int32 CStats::IndustrialPassed;
int32 CStats::SuburbanPassed;
int32 CStats::NumberKillFrenziesPassed;
int32 CStats::PeopleKilledByOthers;
int32 CStats::HelisDestroyed;
int32 CStats::PedsKilledOfThisType[NUM_PEDTYPES];
int32 CStats::TimesDied;
int32 CStats::TimesArrested;
int32 CStats::KillsSinceLastCheckpoint;
float CStats::DistanceTravelledByCar;
float CStats::DistanceTravelledByHelicoptor;
float CStats::DistanceTravelledByBike;
float CStats::DistanceTravelledByBoat;
float CStats::DistanceTravelledByPlane;
float CStats::DistanceTravelledByGolfCart;
float CStats::DistanceTravelledOnFoot;
int32 CStats::FlightTime;
int32 CStats::TimesDrowned;
int32 CStats::PhotosTaken;
float CStats::LoanSharks;
float CStats::StoresKnockedOff;
float CStats::MovieStunts;
float CStats::Assassinations;
float CStats::PizzasDelivered;
float CStats::GarbagePickups;
float CStats::IceCreamSold;
float CStats::TopShootingRangeScore;
float CStats::ShootingRank;
float CStats::ProgressMade;
float CStats::TotalProgressInGame;
int32 CStats::CarsExploded;
int32 CStats::PeopleKilledByPlayer;
float CStats::MaximumJumpDistance;
float CStats::MaximumJumpHeight;
int32 CStats::MaximumJumpFlips;
int32 CStats::MaximumJumpSpins;
int32 CStats::BestStuntJump;
int32 CStats::NumberOfUniqueJumpsFound;
int32 CStats::TotalNumberOfUniqueJumps;
int32 CStats::PassengersDroppedOffWithTaxi;
int32 CStats::MoneyMadeWithTaxi;
int32 CStats::MissionsGiven;
int32 CStats::MissionsPassed;
char CStats::LastMissionPassedName[8];
int32 CStats::TotalLegitimateKills;
int32 CStats::LivesSavedWithAmbulance;
int32 CStats::CriminalsCaught;
int32 CStats::HighestLevelAmbulanceMission;
int32 CStats::HighestLevelVigilanteMission;
int32 CStats::HighestLevelFireMission;
int32 CStats::FiresExtinguished;
int32 CStats::TotalNumberKillFrenzies;
int32 CStats::TotalNumberMissions;
int32 CStats::RoundsFiredByPlayer;
int32 CStats::KgsOfExplosivesUsed;
int32 CStats::BulletsThatHit;
int32 CStats::BestTimeBombDefusal;
int32 CStats::FastestTimes[CStats::TOTAL_FASTEST_TIMES];
int32 CStats::HighestScores[CStats::TOTAL_HIGHEST_SCORES];
int32 CStats::BestPositions[CStats::TOTAL_BEST_POSITIONS];
bool CStats::PropertyOwned[CStats::TOTAL_PROPERTIES];
int32 CStats::NumPropertyOwned;
int32 CStats::PropertyDestroyed;
float CStats::HighestChaseValue;
int32 CStats::CheatedCount;
int32 CStats::ShowChaseStatOnScreen;
int32 CStats::PamphletMissionPassed;
bool CStats::abSonyCDs[1];
int32 CStats::BloodRingKills;
int32 CStats::BloodRingTime;
float CStats::FavoriteRadioStationList[NUM_RADIOS];

int32 CStats::Sprayings;
float CStats::AutoPaintingBudget;
int32 CStats::NoMoreHurricanes;
float CStats::FashionBudget;
float CStats::PropertyBudget;
float CStats::WeaponBudget;
int32 CStats::SafeHouseVisits;
int32 CStats::TyresPopped;

int32 CStats::LongestWheelie;
int32 CStats::LongestStoppie;
int32 CStats::Longest2Wheel;
float CStats::LongestWheelieDist;
float CStats::LongestStoppieDist;
float CStats::Longest2WheelDist;

void CStats::Init()
{
	PeopleKilledByOthers = 0;
	PeopleKilledByPlayer = 0;
	CarsExploded = 0;
	BoatsExploded = 0;
	RoundsFiredByPlayer = 0;
	for (int i = 0; i < NUM_PEDTYPES; i++)
		PedsKilledOfThisType[i] = 0;
	HelisDestroyed = 0;
	ProgressMade = 0.0f;
	KgsOfExplosivesUsed = 0;
	BulletsThatHit = 0;
	TyresPopped = 0;
	HeadsPopped = 0;
	WantedStarsAttained = 0;
	WantedStarsEvaded = 0;
	TimesArrested = 0;
	TimesDied = 0;
	DaysPassed = 0;
	SafeHouseVisits = 0;
	Sprayings = 0;
	MaximumJumpDistance = 0;
	MaximumJumpHeight = 0;
	MaximumJumpFlips = 0;
	MaximumJumpSpins = 0;
	BestStuntJump = 0;
	NumberOfUniqueJumpsFound = 0;
	TotalNumberOfUniqueJumps = 0;
	MissionsGiven = 0;
	MissionsPassed = 0;
	PassengersDroppedOffWithTaxi = 0;
	MoneyMadeWithTaxi = 0;
	DistanceTravelledOnFoot = 0;
	DistanceTravelledByCar = 0;
	DistanceTravelledByBike = 0;
	DistanceTravelledByBoat = 0;
	DistanceTravelledByGolfCart = 0;
	DistanceTravelledByHelicoptor = 0;
#ifdef FIX_BUGS
	DistanceTravelledByPlane = 0;
#endif
	LivesSavedWithAmbulance = 0;
	CriminalsCaught = 0;
	HighestLevelVigilanteMission = 0;
	HighestLevelAmbulanceMission = 0;
	HighestLevelFireMission = 0;
	FiresExtinguished = 0;
	PhotosTaken = 0;
	NumberKillFrenziesPassed = 0;
	TotalNumberKillFrenzies = 0;
	TotalNumberMissions = 0;
	FlightTime = 0;
	TimesDrowned = 0;
	SeagullsKilled = 0;
	WeaponBudget = 0.0f;
	FashionBudget = 0.0f;
	LoanSharks = 0.0f;
	StoresKnockedOff = 0.0f;
	MovieStunts = 0.0f;
	Assassinations = 0.0f;
	PizzasDelivered = 0.0f;
	GarbagePickups = 0.0f;
	IceCreamSold = 0.0f;
	TopShootingRangeScore = 0.0f;
	ShootingRank = 0.0f;
	LongestWheelie = 0;
	LongestStoppie = 0;
	Longest2Wheel = 0;
	LongestWheelieDist = 0.0f;
	LongestStoppieDist = 0.0f;
	Longest2WheelDist = 0.0f;
	PropertyBudget = 0.0f;
	AutoPaintingBudget = 0.0f;
	PropertyDestroyed = 0;
	HighestChaseValue = 0.0f;
	CheatedCount = 0;

	for (int i = 0; i < TOTAL_FASTEST_TIMES; i++)
		FastestTimes[i] = 0;
	for (int i = 0; i < TOTAL_HIGHEST_SCORES; i++)
		HighestScores[i] = 0;
	for (int i = 0; i < TOTAL_BEST_POSITIONS; i++)
		BestPositions[i] = INT_MAX;

	KillsSinceLastCheckpoint = 0;
	TotalLegitimateKills = 0;

	for (int i = 0; i < ARRAY_SIZE(LastMissionPassedName); i++)
		LastMissionPassedName[i] = 0;

	IndustrialPassed = 0;
	CommercialPassed = 0;
	SuburbanPassed = 0;
	PamphletMissionPassed = 0;
	NoMoreHurricanes = 0;
	ShowChaseStatOnScreen = 0;
	for (int i = 0; i < ARRAY_SIZE(abSonyCDs); i++)
		abSonyCDs[i] = 0;
	PopulateFavoriteRadioStationList();

	NumPropertyOwned = 0;
	for (int i = 0; i < TOTAL_PROPERTIES; i++)
		PropertyOwned[i] = false;

	BloodRingKills = 0;
	BloodRingTime = 0;
}

void CStats::RegisterFastestTime(int32 index, int32 time)
{
	assert(index >= 0 && index < TOTAL_FASTEST_TIMES);
	if (FastestTimes[index] == 0)
		FastestTimes[index] = time;
	else
		FastestTimes[index] = Min(FastestTimes[index], time);
}

void CStats::RegisterHighestScore(int32 index, int32 score)
{
	assert(index >= 0 && index < TOTAL_HIGHEST_SCORES);
	HighestScores[index] = Max(HighestScores[index], score);
}

void CStats::RegisterBestPosition(int32 index, int32 position)
{
	assert(index >= 0 && index < TOTAL_BEST_POSITIONS);
	BestPositions[index] = Min(BestPositions[index], position);
}

void CStats::AnotherLifeSavedWithAmbulance()
{
	++LivesSavedWithAmbulance;
}

void CStats::AnotherCriminalCaught()
{
	++CriminalsCaught;
}

void CStats::RegisterLevelAmbulanceMission(int32 level)
{
	HighestLevelAmbulanceMission = Max(HighestLevelAmbulanceMission, level);
}

void CStats::RegisterLevelVigilanteMission(int32 level)
{
	HighestLevelVigilanteMission = Max(HighestLevelVigilanteMission, level);
}

void CStats::RegisterLevelFireMission(int32 level)
{
	HighestLevelFireMission = Max(HighestLevelFireMission, level);
}

void CStats::AnotherFireExtinguished()
{
	++FiresExtinguished;
}

void CStats::AnotherKillFrenzyPassed()
{
	++NumberKillFrenziesPassed;
}

void CStats::SetTotalNumberKillFrenzies(int32 total)
{
	TotalNumberKillFrenzies = total;
}

void CStats::SetTotalNumberMissions(int32 total)
{
	TotalNumberMissions = total;
}

wchar *CStats::FindCriminalRatingString()
{
	int rating = FindCriminalRatingNumber();

	if (rating < 0) {
		if (rating > -500) return TheText.Get("RATNG53");
		if (rating > -2000) return TheText.Get("RATNG54");
		if (rating > -4000) return TheText.Get("RATNG55");
		if (rating > -6000) return TheText.Get("RATNG56");
		return TheText.Get("RATNG57");
	}
	if (rating < 20) return TheText.Get("RATNG1");
	if (rating < 50) return TheText.Get("RATNG2");
	if (rating < 75) return TheText.Get("RATNG3");
	if (rating < 100) return TheText.Get("RATNG4");
	if (rating < 120) return TheText.Get("RATNG5");
	if (rating < 150) return TheText.Get("RATNG6");
	if (rating < 200) return TheText.Get("RATNG7");
	if (rating < 240) return TheText.Get("RATNG8");
	if (rating < 270) return TheText.Get("RATNG9");
	if (rating < 300) return TheText.Get("RATNG10");
	if (rating < 335) return TheText.Get("RATNG11");
	if (rating < 370) return TheText.Get("RATNG12");
	if (rating < 400) return TheText.Get("RATNG13");
	if (rating < 450) return TheText.Get("RATNG14");
	if (rating < 500) return TheText.Get("RATNG15");
	if (rating < 550) return TheText.Get("RATNG16");
	if (rating < 600) return TheText.Get("RATNG17");
	if (rating < 610) return TheText.Get("RATNG18");
	if (rating < 650) return TheText.Get("RATNG19");
	if (rating < 700) return TheText.Get("RATNG20");
	if (rating < 850) return TheText.Get("RATNG21");
	if (rating < 1000) return TheText.Get("RATNG22");
	if (rating < 1005) return TheText.Get("RATNG23");
	if (rating < 1150) return TheText.Get("RATNG24");
	if (rating < 1300) return TheText.Get(TimesArrested > 0 ? "RATNG25" : "RATNG24");
	if (rating < 1500) return TheText.Get("RATNG26");
	if (rating < 1700) return TheText.Get("RATNG27");
	if (rating < 2000) return TheText.Get("RATNG28");
	if (rating < 2100) return TheText.Get("RATNG29");
	if (rating < 2300) return TheText.Get("RATNG30");
	if (rating < 2500) return TheText.Get("RATNG31");
	if (rating < 2750) return TheText.Get("RATNG32");
	if (rating < 3000) return TheText.Get("RATNG33");
	if (rating < 3500) return TheText.Get("RATNG34");
	if (rating < 4000) return TheText.Get("RATNG35");
	if (rating < 5000) return TheText.Get("RATNG36");
	if (rating < 7500) return TheText.Get("RATNG37");
	if (rating < 10000) return TheText.Get("RATNG38");
	if (rating < 20000) return TheText.Get("RATNG39");
	if (rating < 30000) return TheText.Get("RATNG40");
	if (rating < 40000) return TheText.Get("RATNG41");
	if (rating < 50000) return TheText.Get("RATNG42");
	if (rating < 65000) return TheText.Get("RATNG43");
	if (rating < 80000) return TheText.Get("RATNG44");
	if (rating < 100000) return TheText.Get("RATNG45");
	if (rating < 150000) return TheText.Get("RATNG46");
	if (rating < 200000) return TheText.Get("RATNG47");
	if (rating < 300000) return TheText.Get("RATNG48");
	if (rating < 375000) return TheText.Get("RATNG49");
	if (rating < 500000) return TheText.Get(FlightTime / 60000 / 60 > 10 ? "RATNG50" : "RATNG49");
	if (rating < 1000000) return TheText.Get("RATNG51");
	return TheText.Get(CWorld::Players[CWorld::PlayerInFocus].m_nVisibleMoney > 10000000 ? "RATNG52" : "RATNG51");
}

wchar *CStats::FindChaseString(float fMediaLevel) {
	if (fMediaLevel < 20.0f) return TheText.Get("CHASE1");
	if (fMediaLevel < 50.0f) return TheText.Get("CHASE2");
	if (fMediaLevel < 75.0f) return TheText.Get("CHASE3");
	if (fMediaLevel < 100.0f) return TheText.Get("CHASE4");
	if (fMediaLevel < 150.0f) return TheText.Get("CHASE5");
	if (fMediaLevel < 200.0f) return TheText.Get("CHASE6");
	if (fMediaLevel < 250.0f) return TheText.Get("CHASE7");
	if (fMediaLevel < 300.0f) return TheText.Get("CHASE8");
	if (fMediaLevel < 350.0f) return TheText.Get("CHASE9");
	if (fMediaLevel < 400.0f) return TheText.Get("CHASE10");
	if (fMediaLevel < 500.0f) return TheText.Get("CHASE11");
	if (fMediaLevel < 600.0f) return TheText.Get("CHASE12");
	if (fMediaLevel < 700.0f) return TheText.Get("CHASE13");
	if (fMediaLevel < 800.0f) return TheText.Get("CHASE14");
	if (fMediaLevel < 900.0f) return TheText.Get("CHASE15");
	if (fMediaLevel < 1000.0f) return TheText.Get("CHASE16");
	if (fMediaLevel < 1200.0f) return TheText.Get("CHASE17");
	if (fMediaLevel < 1400.0f) return TheText.Get("CHASE18");
	if (fMediaLevel < 1600.0f) return TheText.Get("CHASE19");
	if (fMediaLevel < 1800.0f) return TheText.Get("CHASE20");
	return TheText.Get("CHASE21");
}

int32 CStats::FindCriminalRatingNumber()
{
	int32 rating;

	rating = FiresExtinguished + 10 * HighestLevelFireMission + 10 * HighestLevelAmbulanceMission
		+ CriminalsCaught + LivesSavedWithAmbulance
		+ 30 * HelisDestroyed + TotalLegitimateKills - 3 * TimesArrested - 3 * TimesDied
		+ CWorld::Players[CWorld::PlayerInFocus].m_nMoney / 5000;
	if (CPad::bHasPlayerCheated || CheatedCount > 0) {
		rating -= CheatedCount;
		if (rating <= -10000)
			rating = -10000;

	} else if (rating
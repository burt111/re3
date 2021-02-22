                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ctorList(CPtrList &list, const CColLine &line, CColPoint &point, float &dist, CEntity *&entity, bool ignoreSeeThrough, CStoredCollPoly *poly);
	static bool GetIsLineOfSightClear(const CVector &point1, const CVector &point2, bool checkBuildings, bool checkVehicles, bool checkPeds, bool checkObjects, bool checkDummies, bool ignoreSeeThrough, bool ignoreSomeObjects = false);
	static bool GetIsLineOfSightSectorClear(CSector &sector, const CColLine &line, bool checkBuildings, bool checkVehicles, bool checkPeds, bool checkObjects, bool checkDummies, bool ignoreSeeThrough, bool ignoreSomeObjects = false);
	static bool GetIsLineOfSightSectorListClear(CPtrList &list, const CColLine &line, bool ignoreSeeThrough, bool ignoreSomeObjects = false);
	
	static CEntity *TestSphereAgainstWorld(CVector centre, float radius, CEntity *entityToIgnore, bool checkBuildings, bool checkVehicles, bool checkPeds, bool checkObjects, bool checkDummies, bool ignoreSomeObjects);
	static CEntity *TestSphereAgainstSectorList(CPtrList&, CVector, float, CEntity*, bool);
	static void FindObjectsInRangeSectorList(CPtrList &list, Const CVector &centre, float radius, bool ignoreZ, int16 *numObjects, int16 lastObject, CEntity **objects);
	static void FindObjectsInRange(Const CVector &centre, float radius, bool ignoreZ, int16 *numObjects, int16 lastObject, CEntity **objects, bool checkBuildings, bool checkVehicles, bool checkPeds, bool checkObjects, bool checkDummies);
	static void FindObjectsOfTypeInRangeSectorList(uint32 modelId, CPtrList& list, const CVector& position, float radius, bool bCheck2DOnly, int16* nEntitiesFound, int16 maxEntitiesToFind, CEntity** aEntities);
	static void FindObjectsOfTypeInRange(uint32 modelId, const CVector& position, float radius, bool bCheck2DOnly, int16* nEntitiesFound, int16 maxEntitiesToFind, CEntity** aEntities, bool bBuildings, bool bVehicles, bool bPeds, bool bObjects, bool bDummies);
	static float FindGroundZForCoord(float x, float y);
	static float FindGroundZFor3DCoord(float x, float y, float z, bool *found);
	static float FindRoofZFor3DCoord(float x, float y, float z, bool *found);
	static void RemoveReferencesToDeletedObject(CEntity*);
	static void FindObjectsKindaColliding(const CVector& position, float radius, bool bCheck2DOnly, int16* nCollidingEntities, int16 maxEntitiesToFind, CEntity** aEntities, bool bBuildings, bool bVehicles, bool bPeds, bool bObjects, bool bDummies);
	static void FindObjectsKindaCollidingSectorList(CPtrList& list, const CVector& position, float radius, bool bCheck2DOnly, int16* nCollidingEntities, int16 maxEntitiesToFind, CEntity** aEntities);
	static void FindObjectsIntersectingCube(const CVector& vecStartPos, const CVector& vecEndPos, int16* nIntersecting, int16 maxEntitiesToFind, CEntity** aEntities, bool bBuildings, bool bVehicles, bool bPeds, bool bObjects, bool bDummies);
	static void FindObjectsIntersectingCubeSectorList(CPtrList& list, const CVector& vecStartPos, const CVector& vecEndPos, int16* nIntersecting, int16 maxEntitiesToFind, CEntity** aEntities);
	static void FindObjectsIntersectingAngledCollisionBox(const CBox &, const CMatrix &, const CVector &, float, float, float, float, int16*, int16, CEntity **, bool, bool, bool, bool, bool);
	static void FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList& list, const CBox& boundingBox, const CMatrix& matrix, const CVector& position, int16* nEntitiesFound, int16 maxEntitiesToFind, CEntity** aEntities);
	static void FindMissionEntitiesIntersectingCube(const CVector& vecStartPos, const CVector& vecEndPos, int16* nIntersecting, int16 maxEntitiesToFind, CEntity** aEntities, bool bVehicles, bool bPeds, bool bObjects);
	static void FindMissionEntitiesIntersectingCubeSectorList(CPtrList& list, const CVector& vecStartPos, const CVector& vecEndPos, int16* nIntersecting, int16 maxEntitiesToFind, CEntity** aEntities, bool bIsVehicleList, bool bIsPedList);

	static void ClearCarsFromArea(float x1, float y1, float z1, float x2, float y2, float z2);
	static void ClearPedsFromArea(float x1, float y1, float z1, float x2, float y2, float z2);
	static void CallOffChaseForArea(float x1, float y1, float x2, float y2);
	static void CallOffChaseForAreaSectorListVehicles(CPtrList& list, float x1, float y1, float x2, float y2, float fStartX, float fStartY, float fEndX, float fEndY);
	static void CallOffChaseForAreaSectorListPeds(CPtrList& list, float x1, float y1, float x2, float y2);

	static bool IsWanderPathClear(CVector const&, CVector const&, float, int);

	static float GetSectorX(float f) { return ((f - WORLD_MIN_X)/SECTOR_SIZE_X); }
	static float GetSectorY(float f) { return ((f - WORLD_MIN_Y)/SECTOR_SIZE_Y); }
	static int GetSectorIndexX(float f) { return (int)GetSectorX(f); }
	static int GetSectorIndexY(float f) { return (int)GetSectorY(f); }
	static float GetWorldX(int x) { return x*SECTOR_SIZE_X + WORLD_MIN_X; }
	static float GetWorldY(int y) { return y*SECTOR_SIZE_Y + WORLD_MIN_Y; }

	static void RemoveEntityInsteadOfProcessingIt(CEntity* ent);
	static void RemoveFallenPeds();
	static void RemoveFallenCars();

	static void StopAllLawEnforcersInTheirTracks();
	static void SetAllCarsCanBeDamaged(bool);
	static void ExtinguishAllCarFiresInArea(CVector, float);
	static void SetCarsOnFire(float x, float y, float z, float radius, CEntity* reason);
	static void SetPedsChoking(float x, float y, float z, float radius, CEntity* reason);
	static void SetPedsOnFire(float x, float y, float z, float radius, CEntity* reason);

	static void Initialise();
	static void AddParticles();
	static void ShutDown();
	static void ClearForRestart(void);
	static void RepositionCertainDynamicObjects();
	static void RepositionOneObject(CEntity* pEntity);
	static void RemoveStaticObjects();
	static void Process();
	static void TriggerExplosion(const CVector& position, float fRadius, float fPower, CEntity* pCreator, bool bProcessVehicleBombTimer);
	static void TriggerExplosionSectorList(CPtrList& list, const CVector& position, float fRadius, float fPower, CEntity* pCreator, bool bProcessVehicleBombTimer);
	static void UseDetonator(CEntity *pEntity);

	// NB: following functions are unused (TODO?)
	static void CastShadow(float, float, float, float);
	static void CastShadowSectorList(CPtrList&, float, float, float, float);
	static void FindLowestZForCoord(float, float);
	static void CheckBlockListIntegrity(void);
	static void ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList&, const CColLine&, CEntity*&, bool, CStoredCollPoly*);
	static void ProcessVerticalLineSector_FillGlobeColPoints(CSector&, const CColLine&, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*);
	static void ProcessVerticalLine_FillGlobeColPoints(const CVector&, float, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*);
	static void PrintCarChanges(void);
	static void TestForBuildingsOnTopOfEachOther(CPtrList&);
	static void TestForBuildingsOnTopOfEachOther(void);
	static void TestForUnusedModels(CPtrList&, int*);
	static void TestForUnusedModels(void);
	static void HandleCollisionZoneChange(eLevelName, eLevelName);
	static void DoZoneTestForChaser(class CPhysical*);
	static void FindPlayerSlotWithPedPointer(void*);
};

extern CColPoint gaTempSphereColPoints[MAX_COLLISION_POINTS];

#pragma once

#include "Main.h"

class COther
{
public:
	void Bunnyhop(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal);
	void AutoPistol(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon);
	void RankReveal(CInput::CUserCmd* pUserCmd);
};

extern COther g_pOther;
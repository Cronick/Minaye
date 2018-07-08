#include "Other.h"

COther g_pOther;

void COther::Bunnyhop(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal)
{
	static bool bLastJumped = false;
	static bool bShouldFake = false;

	if (!bLastJumped && bShouldFake)
	{
		bShouldFake = false;
		pUserCmd->buttons |= IN_JUMP;
	}
	else if (pUserCmd->buttons & IN_JUMP)
	{
		if (pLocal->GetFlags() & FL_ONGROUND)
		{
			bLastJumped = true;
			bShouldFake = true;
		}
		else
		{
			pUserCmd->buttons &= ~IN_JUMP;
			bLastJumped = false;
		}
	}
	else
	{
		bLastJumped = false;
		bShouldFake = false;
	}
}

void COther::AutoPistol(CInput::CUserCmd* pUserCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon)
{
	if (pWeapon->GetWeaponID() == WEAPON_DEAGLE)
		return;

	if (!pWeapon->IsPistol())
		return;

	if (pWeapon->GetClip1() == 0)
		return;

	if (pUserCmd->buttons & IN_ATTACK)
	{
		float flServerTime = (float)pLocal->GetTickBase() * g_pGlobalVars->interval_per_tick;
		float flNextPrimaryAttack = pWeapon->GetNextPrimaryAttack();

		if (flNextPrimaryAttack > flServerTime)
			pUserCmd->buttons &= ~IN_ATTACK;
	}
}

void COther::RankReveal(CInput::CUserCmd* pUserCmd)
{
	using RevealAllFn = void(*)(int);
	static RevealAllFn fnReveal = (RevealAllFn)PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL);

	int iBuffer[1];

	if (pUserCmd->buttons & IN_SCORE)
		fnReveal(iBuffer[1]);
}
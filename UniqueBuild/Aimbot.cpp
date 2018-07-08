#include "Aimbot.h"

CAim g_pAim;

CBaseCombatWeapon* CAim::GetActiveWeapon(CBaseEntity *pEntity)
{
	ULONG hHandle = (ULONG)*(PDWORD)((DWORD)pEntity + Offsets::Player::m_hActiveWeapon);
	//if (!hHandle) return nullptr;
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)g_pEntList->GetClientEntityFromHandle(hHandle);
	//if (!pWeapon) return nullptr;
	return pWeapon;
}

float RandomFloat(float min, float max)
{
	static auto ranFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandle("vstdlib.dll"), "RandomFloat"));
	if (ranFloat)
		return ranFloat(min, max);
	else
		return 0.f;
}

void Smooth(CInput::CUserCmd *pCmd, Vector& vAim, const char *var)
{
	Vector vDelta = pCmd->viewangles - vAim;
	g_pTools.NormalizeVector(vDelta);

	Vector NormalizedSmooth = pCmd->viewangles - vDelta / g_pCvar.getValue(var) * 0.5;
	g_pTools.NormalizeVector(NormalizedSmooth);

	vAim = NormalizedSmooth;
}

void RecoilControl(Vector& vecPunchAngles, Vector& vecAimAngles)
{
	vecPunchAngles *= 2.f;

	float fLength = g_pMath.VectorNormalize(vecPunchAngles);
	fLength -= (10.f + fLength * 0.5f) * g_pGlobalVars->interval_per_tick;
	fLength = max(fLength, 0.f);
	vecPunchAngles *= fLength;

	g_pTools.NormalizeVector(vecPunchAngles);
	g_pTools.ClampAngle(vecPunchAngles);
	vecAimAngles -= vecPunchAngles;
}

float GetFoV(Vector vLocalOrigin, Vector vPosition, Vector vForward)
{
	Vector vLocal;
	VectorSubtract(vPosition, vLocalOrigin, vLocal);
	vLocal.NormalizeInPlace();

	float fValue = vForward.Dot(vLocal);
	if (fValue < -1.0f)
		fValue = -1.0f;
	if (fValue > 1.0f)
		fValue = 1.0f;

	return RAD2DEG(acos(fValue));
}

Vector CAim::Randomize(Vector vAngles)
{
	if (abs(flCurrentX - flTargetDestX) < .05f)
	{
		flTargetDestX = rand() % (int)(30 * 10) + 1;
		flTargetDestX /= 500;

		int iRand = rand() % 2 + 1;
		if (iRand == 2)
			flTargetDestX = -flTargetDestX;
	}

	if (abs(flCurrentY - flTargetDestY) < .05f)
	{
		flTargetDestY = rand() % (int)(30 * 10) + 1;
		flTargetDestY /= 500;

		int iRand = rand() % 2 + 1;
		if (iRand == 2)
			flTargetDestY = -flTargetDestY;
	}

	flCurrentX += (flTargetDestX - flCurrentX) / 2;
	flCurrentY += (flTargetDestY - flCurrentY) / 2;

	vAngles.x += flCurrentY;
	vAngles.y += flCurrentY;

	flX = flCurrentX;
	flY = flCurrentY;

	return vAngles;
}

void CAim::doAim(CInput::CUserCmd* pCmd, CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon)
{
	if (!GetAsyncKeyState(g_pCvar.getValue("aimbot_key")))
		return;

	if (pWeapon->IsOther() || pWeapon->IsGrenade() || pWeapon->IsKnife())
		return;

	static Vector vClientViewAngles;
	g_pEngine->GetViewAngles(vClientViewAngles);

	static Vector vAngle;
	g_pMath.AngleVectors(vClientViewAngles, vAngle);

	ResetRCS();

	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (pEntity->IsProtected())
			continue;
		if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
			continue;
		if (!g_pMath.GetHitboxPosition(g_pCvar.getValue("aimbot_spot"), vRCSTarget, pLocal->GetAbsAngles(), i))
			continue;
		if (!g_pTools.IsVisible(pLocal->GetEyePosition(), vRCSTarget, pEntity))
			continue;

		float fCurrentFOV = GetFoV(pLocal->GetEyePosition(), vRCSTarget, vAngle);
		if (fBestRCSTarget < fCurrentFOV)
			continue;

		fBestRCSTarget = fCurrentFOV;
		vRCSFinal = vRCSTarget;
		iRCSTarget = i;
	}

	if (HasTargetRCS())
	{
		float fLen = Vector(vRCSFinal - pLocal->GetEyePosition()).Length();

		Vector vAngle;
		g_pMath.CalcAngle(pLocal->GetEyePosition(), vRCSFinal, vAngle);
		g_pTools.NormalizeVector(vAngle);

		if (g_pCvar.getValue("aimbot_rcs") == 1)
		{
			Vector vPunchangle = pLocal->vecGetPunchAngle();

			if (pWeapon->GetWeaponID() != WEAPON_DEAGLE)
				RecoilControl(vPunchangle, vAngle);

			g_pTools.NormalizeVector(vAngle);
		}

		static Vector vForward;
		g_pMath.AngleVectors(vAngle, vForward);
		vForward = (vForward * fLen) + pLocal->GetEyePosition();

		if (g_pMath.GetFov2(pCmd->viewangles, pLocal->GetEyePosition(), vForward, g_pCvar.getValue("aimbot_distance_fov")) <= g_pCvar.getValue("aimbot_fov"))
		{
			if (g_pCvar.getValue("aimbot_smooth") > 0) {
				Smooth(pCmd, vAngle, "aimbot_smooth");
			}

			if (g_pCvar.getValue("aimbot_silent") == 1) {
				pCmd->viewangles = vAngle;
			} else {
				g_pTools.ClampAngle(vAngle);
				g_pTools.NormalizeVector(vAngle);
				g_pEngine->SetViewAngles(vAngle);
			}

			if (g_pCvar.getValue("aimbot_autofire") == 1) {
				pCmd->buttons |= IN_ATTACK;
			}
		}
	}
}

void CAim::DoNoRecoil(CInput::CUserCmd* pCmd)
{
	// Ghetto rcs shit, implement properly later
	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (pLocal != nullptr)
	{
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			pCmd->viewangles -= AimPunch * 2;
			g_pTools.NormalizeVector(pCmd->viewangles);
		}
	}
}

void CAim::DoAntiAim(CInput::CUserCmd* pCmd, CBaseEntity* pLocal)
{
	CBaseEntity* pEntity = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

	if (pCmd->buttons & IN_USE)
		return;

	if (pEntity->IsProtected() || pEntity->GetFlags() & FL_FROZEN)
		return;

	CBaseCombatWeapon* pWeapon = g_pAim.GetActiveWeapon(pLocal);

	if (!pWeapon)
		return;

	if (pWeapon->GetWeaponID() == WEAPON_R8REVOLVER)
	{
		if (pCmd->buttons & IN_ATTACK2)
			return;
	}
	else
	{
		if (pWeapon->IsKnife() && ((pCmd->buttons & IN_ATTACK) || (pCmd->buttons & IN_ATTACK2)))
			return;
		else if ((pCmd->buttons & IN_ATTACK) && (pWeapon->GetWeaponID() != WEAPON_C4))
			return;
	}

	float curpos = pCmd->viewangles.y + 180.f;

	pCmd->viewangles = Vector(88.99f, curpos + RandomFloat(-135.f, 135.f), 0);
}
#include "Wallhack.h"
#include <algorithm>

CWallhack g_pWallhack;

struct ESPBox
{
	int x, y, w, h, gay;
};

float CSGO_Armor(float flDamage, int ArmorValue)
{
	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	if (ArmorValue > 0) {
		float flNew = flDamage * flArmorRatio;
		float flArmor = (flDamage - flNew) * flArmorBonus;

		if (flArmor > static_cast<float>(ArmorValue)) {
			flArmor = static_cast<float>(ArmorValue) * (1.f / flArmorBonus);
			flNew = flDamage - flArmor;
		}

		flDamage = flNew;
	}
	return flDamage;
}

float damage;
char bombdamagestringdead[24];
char bombdamagestringalive[24];

void BoundingBox(CBaseEntity* pEntity, int r, int g, int b, int a, const char* name)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)pEntity + Offsets::Entity::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMins);
	Vector max = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMaxs);

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	Vector pointsTransformed[8];

	for (int i = 0; i < 8; i++)
		g_pMath.VectorTransform(points[i], trans, pointsTransformed[i]);

	Vector flb;
	Vector brt;
	Vector blb;
	Vector frt;
	Vector frb;
	Vector brb;
	Vector blt;
	Vector flt;

	if (!g_pDebugOverlay->ScreenPosition(pointsTransformed[3], flb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[5], brt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[0], blb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[4], frt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[2], frb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[1], brb) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[6], blt) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[7], flt) != 1)
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bot = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bot < arr[i].y)
			bot = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	float h = (bot - top);
	float w = h / 2;

	g_pDraw.LineRGBA(left, top, right, top, r, g, b, a);
	g_pDraw.LineRGBA(left - 1, top - 1, right + 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, bot, left, bot, r, g, b, a);
	g_pDraw.LineRGBA(right + 1, bot + 1, left - 1, bot + 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(left, bot, left, top, r, g, b, a);
	g_pDraw.LineRGBA(left - 1, bot + 1, left - 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, top, right, bot, r, g, b, a);
	g_pDraw.LineRGBA(right + 1, top - 1, right + 1, bot + 1, 0, 0, 0, a);

	g_pDraw.DrawString(g_pDraw.esp_font, true, left + w, top - 15, r, g, b, a, name);
}

void BoundingBox_nade(CBaseEntity* pEntity, int r, int g, int b, int a, const char* name)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)pEntity + Offsets::Entity::m_rgflCoordinateFrame);

	Vector min = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMins);
	Vector max = *(Vector*)((DWORD)pEntity + Offsets::Entity::m_Collision + Offsets::Entity::m_vMaxs);

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	Vector pointsTransformed[8];

	for (int i = 0; i < 8; i++)
		g_pMath.VectorTransform(points[i], trans, pointsTransformed[i]);

	Vector flb;
	Vector brt;
	Vector blb;
	Vector frt;
	Vector frb;
	Vector brb;
	Vector blt;
	Vector flt;

	if (!g_pDebugOverlay->ScreenPosition(pointsTransformed[3], flb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[5], brt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[0], blb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[4], frt) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[2], frb) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[1], brb) != 1
		|| !g_pDebugOverlay->ScreenPosition(pointsTransformed[6], blt) != 1 || !g_pDebugOverlay->ScreenPosition(pointsTransformed[7], flt) != 1)
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bot = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bot < arr[i].y)
			bot = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	float h = (bot - top);
	float w = h / 2;

	g_pDraw.LineRGBA(left, top, right, top, 255, 255, 255, 255);
	g_pDraw.LineRGBA(left - 1, top - 1, right + 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, bot, left, bot, 255, 255, 255, 255);
	g_pDraw.LineRGBA(right + 1, bot + 1, left - 1, bot + 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(left, bot, left, top, 255, 255, 255, 255);
	g_pDraw.LineRGBA(left - 1, bot + 1, left - 1, top - 1, 0, 0, 0, a);

	g_pDraw.LineRGBA(right, top, right, bot, 255, 255, 255, 255);
	g_pDraw.LineRGBA(right + 1, top - 1, right + 1, bot + 1, 0, 0, 0, a);

	g_pDraw.DrawString(g_pDraw.esp_font, true, left + w, bot + 2, r, g, b, a, name);
}

void DrawEntityESP(CBaseEntity* pEntity)
{
	if (pEntity->GetAbsAngles().x == 0.f && pEntity->GetAbsAngles().z == 0.f)
		return;

	std::string szCurrenModelName = g_pModel->GetModelName(pEntity->GetModel());
	if (szCurrenModelName.find("dropped", 0) != std::string::npos)
	{
		if (szCurrenModelName.find("eq_", 0) != std::string::npos)
			return;

		szCurrenModelName.erase(0, szCurrenModelName.find_first_of("_", std::string("abc").length()) + 1);
		szCurrenModelName.erase(szCurrenModelName.find_last_of("_"), 12);

		if (!strcmp(szCurrenModelName.c_str(), "ied"))
			szCurrenModelName = "C4";
		else if (!strcmp(szCurrenModelName.c_str(), "223"))
			szCurrenModelName = "USP-S";
		else if (!strcmp(szCurrenModelName.c_str(), "75"))
			szCurrenModelName = "CZ75";
		else if (!strcmp(szCurrenModelName.c_str(), "s"))
			szCurrenModelName = "M4A1-S";

		BoundingBox(pEntity, 255, 255, 255, 255, szCurrenModelName.c_str());
	}
}

void DrawHead(CBaseEntity* pLocal, int pEntityIndex, CBaseEntity* pEntity)
{
	Vector vPlayer;
	g_pMath.GetHitboxPosition(g_pCvar.getValue("aimbot_spot"), vPlayer, pLocal->GetAbsAngles(), pEntityIndex);

	Vector vHead;
	if (g_pDebugOverlay->ScreenPosition(vPlayer, vHead) != 1)
	{
		g_pDraw.FillRGBA(vHead.x, vHead.y, 4, 4, 255, 255, 255, 255);
		g_pDraw.DrawOutlineRect(vHead.x, vHead.y, 4, 4, 0, 0, 0, 255);
	}
}

__forceinline float DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void Chicken(CBaseEntity* pEntity, int iIndex)
{
	if (pEntity->GetClientClass()->GetClassID() == CChicken)
		BoundingBox(pEntity, 50, 150, 200, 255, "Chicken");
}

void Bomb(CBaseEntity* pEntity)
{
	Vector vPlayer, vScreen;

	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (!pLocal)
		return;

	if (pEntity->GetClientClass()->GetClassID() == CPlantedC4)
	{
		if (pEntity->GetIsTicking())
		{
			float flBombTimer = pEntity->GetBombTimer();
			float flTimeLeft = (g_pGlobalVars->curtime - flBombTimer) * -1;
			if (flTimeLeft < 0)
				flTimeLeft = 0;

			vPlayer = pEntity->GetAbsOrigin();
			if (g_pDebugOverlay->ScreenPosition(vPlayer, vScreen) != 1)
				g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y, 255, 255, 255, 255, "%2.1f Seconds", flTimeLeft);

				float flDistance = pLocal->GetEyePosition().DistTo(pEntity->GetEyePosition());

				float a = 450.7f;
				float b = 75.68f;
				float c = 789.2f;
				float d = ((flDistance - b) / c);
				float flDamage = a * exp(-d * d);

				damage = float((std::max)((int)ceilf(CSGO_Armor(flDamage, pLocal->GetArmorValue())), 0));
				sprintf_s(bombdamagestringdead, sizeof(bombdamagestringdead) - 1, "ur dead nigga");
				sprintf_s(bombdamagestringalive, sizeof(bombdamagestringalive) - 1, "Health Left: %.0f", pLocal->GetHealth() - damage);

				if (damage >= pLocal->GetHealth())
				{
					g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 10, 255, 0, 0, 255, bombdamagestringdead);
				}
				else if (pLocal->GetHealth() > damage)
				{
					g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 10, 255, 255, 255, 255, bombdamagestringalive);
				}
		}
	}

	for (int i = 1; i < g_pEngine->GetMaxClients(); i++)
	{
		CBaseEntity* pDefuser = g_pEntList->GetClientEntity(i);
		if (!pDefuser)
			continue;
		if (pDefuser->IsDormant())
			continue;
		if (pDefuser->GetLifeState() != LIFE_ALIVE)
			continue;

		if (pDefuser->isDefusing() && pEntity->GetClientClass()->GetClassID() == CPlantedC4)
		{
			if (pEntity->GetIsTicking())
			{
				float flDefuseTimer = pEntity->GetDefuseTimer();

				float TimeLeft = (g_pGlobalVars->curtime - flDefuseTimer) * -1;

				if (TimeLeft < 0)
					TimeLeft = 0;

				vPlayer = pEntity->GetAbsOrigin();

				if (g_pDebugOverlay->ScreenPosition(vPlayer, vScreen) != 1 && TimeLeft > 0)
				{
					if (pDefuser->hasDefuse() == 0)
						g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 8, 0, 255, 0, 255, "%2.1f without Kit", TimeLeft);
					else
						g_pDraw.DrawString(g_pDraw.esp_font, true, vScreen.x, vScreen.y + 8, 255, 255, 0, 255, "%2.1f with Kit", TimeLeft);
				}
			}
		}
	}
}

void DrawGrenades(CBaseEntity* pEntity)
{
	model_t* nadeModel = (model_t*)pEntity->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = g_pModel->GetStudiomodel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped"))
		return;

	Color colGrenadeColor = Color(0, 0, 0, 0);
	char* nadeName = "Unknown Grenade";

	IMaterial* mats[32];
	g_pModel->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), "flashbang"))
		{
			colGrenadeColor = Color(255, 255, 0, 255);
			nadeName = "Flash";
			break;
		}
		else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
		{
			colGrenadeColor = Color(255, 0, 0, 255);
			nadeName = "HE Grenade";
			break;
		}
		else if (strstr(mat->GetName(), "smoke"))
		{
			colGrenadeColor = Color(0, 255, 0, 255);
			nadeName = "Smoke";
			break;
		}
		else if (strstr(mat->GetName(), "decoy"))
		{
			colGrenadeColor = Color(0, 255, 0, 255);
			nadeName = "Decoy";
			break;
		}
		else if (strstr(mat->GetName(), "incendiary") || strstr(mat->GetName(), "molotov"))
		{
			colGrenadeColor = Color(255, 0, 0, 255);
			nadeName = "Molotov";
			break;
		}
	}
	BoundingBox_nade(pEntity, colGrenadeColor.r(), colGrenadeColor.g(), colGrenadeColor.b(), 255, nadeName);
}

void Money(CBaseEntity* pEntity, CBaseEntity* pLocal)
{
	if (GetAsyncKeyState(VK_TAB)) {
		static int y = 357;

		for (int i = 1; i <= 64; i++) {
			CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
			CEngineClient::player_info_t Info;

			if (!g_pEngine->GetPlayerInfo(i, &Info))
				continue;

			if (pEntity == nullptr || Info.fakeplayer)
				continue;

			if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
				continue;

			if (pLocal->GetTeamNumber() == 2) { // T
				g_pDraw.DrawString(g_pDraw.font_money, true, 1130, y, 126, 180, 224, 255, "$%i", pEntity->GetMoney());
			}
			else if (pLocal->GetTeamNumber() == 3) { // CT
				g_pDraw.DrawString(g_pDraw.font_money, true, 1130, y + 258, 226, 203, 129, 255, "$%i", pEntity->GetMoney());
			}
			y += 29;
		}
		y = 357;
	}
}

void CWallhack::doDraw()
{
	if (g_pEngine->isinGame())
	{
		CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
		if (!pLocal)
			return;

		for (int i = 1; i < g_pEntList->GetHighestEntityIndex(); i++)
		{
			CBaseEntity* pEntity = g_pEntList->GetClientEntity(i);
			if (!pEntity)
				continue;

			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

			if (g_pCvar.getValue("esp_nade") == 1 && strstr(cClass->GetName(), "Projectile"))
				DrawGrenades(pEntity);

			if (g_pCvar.getValue("esp_bombinfo") == 1)
				Bomb(pEntity);

			if (g_pCvar.getValue("esp_chicken") == 1)
				Chicken(pEntity, i);

			if (g_pCvar.getValue("esp_droppedweapons") == 1)
				DrawEntityESP(pEntity);

			if (g_pCvar.getValue("esp_money") == 1)
				Money(pEntity, pLocal);

			if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
				continue;
			if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
				continue;
			if (pEntity->GetTeamNumber() == pLocal->GetTeamNumber())
				continue;

			Vector vScreenBot, vScreenTop;
			Vector vTop, vBot;
			vBot = pEntity->GetAbsOrigin();
			
			bool isEnemyVis = g_pTools.IsVisible(pLocal->GetEyePosition(), pEntity->GetEyePosition(), pEntity) && pLocal->GetTeamNumber() != pEntity->GetTeamNumber();

			int r, g, b;
			if (pEntity->GetTeamNumber() == 2) // terrorists
				isEnemyVis ? r = g_pCvar.getValue("esp_t_visible_color_r") : r = g_pCvar.getValue("esp_t_invisible_color_r"), isEnemyVis ? g = g_pCvar.getValue("esp_t_visible_color_g") : g = g_pCvar.getValue("esp_t_invisible_color_g"), isEnemyVis ? b = g_pCvar.getValue("esp_ct_visible_color_b") : b = g_pCvar.getValue("esp_t_invisible_color_b");
			else if (pEntity->GetTeamNumber() == 3 ) // counter terrorists
				isEnemyVis ? r = g_pCvar.getValue("esp_ct_visible_color_r") : r = g_pCvar.getValue("esp_t_invisible_color_r"), isEnemyVis ? g = g_pCvar.getValue("esp_ct_visible_color_g") : g = g_pCvar.getValue("esp_ct_invisible_color_g"), isEnemyVis ? b = g_pCvar.getValue("esp_ct_visible_color_b") : b = g_pCvar.getValue("esp_ct_invisible_color_b");

			if (g_pCvar.getValue("esp_drawspot") == 1)
				DrawHead(pLocal, i, pEntity);

			if (g_pCvar.getValue("esp_skeleton") == 1)
				g_pDraw.DrawBone(pEntity, i, 255);

			if (pEntity->GetFlags() & FL_DUCKING)
				vTop = vBot + Vector(0, 0, 55.f);
			else
				vTop = vBot + Vector(0, 0, 75.f);

			int iHealth = pEntity->GetHealth();

			if (g_pDebugOverlay->ScreenPosition(vBot, vScreenBot) != 1 && g_pDebugOverlay->ScreenPosition(vTop, vScreenTop) != 1)
			{
				float h = (vScreenBot.y - vScreenTop.y);
				float w = (vScreenBot.y - vScreenTop.y) / 4;
				float healthbarh = w * 2.5;
				float rechts = w * 1.7;

				CEngineClient::player_info_t pInfo;
				if (g_pEngine->GetPlayerInfo(i, &pInfo))
				{
					if (g_pCvar.getValue("esp_box") == 1)
						g_pDraw.DrawEspBox(vScreenTop.x - w, vScreenTop.y + 1, w * 2, h, r, g, b, 255);

					if (g_pCvar.getValue("esp_name") == 1)
						//g_pDraw.DrawString(g_pDraw.esp_font, true, vScreenTop.x, vScreenTop.y - 13, 255, 255, 255, 255, pInfo.name);
						g_pDraw.DrawString(g_pDraw.esp_font, false, vScreenTop.x + w + 6, vScreenTop.y, g_pCvar.getValue("esp_text_color_r"), g_pCvar.getValue("esp_text_color_g"), g_pCvar.getValue("esp_text_color_b"), 255, pInfo.name);

					if (g_pCvar.getValue("esp_health") == 1)
						g_pDraw.DrawHealthBar(vScreenTop.x - w - 5, vScreenBot.y - h / 2, 4, h, 255.f - iHealth * 2.55f, iHealth * 2.55f, 0, 255, pEntity->GetHealth());

					if (g_pCvar.getValue("esp_weapon") == 1) {
						//g_pDraw.DrawString(g_pDraw.esp_font, true, vScreenTop.x, vScreenBot.y - 16, 255, 255, 255, 255, g_pAim.GetActiveWeapon(pEntity)->GetWeaponName());
						//g_pDraw.DrawString(g_pDraw.esp_font, false, vScreenTop.x + w + 6, vScreenTop.y + 20, g_pCvar.getValue("esp_text_color_r"), g_pCvar.getValue("esp_text_color_g"), g_pCvar.getValue("esp_text_color_b"), 255, g_pAim.GetActiveWeapon(pEntity)->GetWeaponName());
						g_pDraw.DrawString(g_pDraw.esp_font, false, vScreenTop.x + w + 6, vScreenTop.y + 20, g_pCvar.getValue("esp_text_color_r"), g_pCvar.getValue("esp_text_color_g"), g_pCvar.getValue("esp_text_color_b"), 255, g_pAim.GetActiveWeapon(pEntity)->GetWeaponName());
					}
				}
			}
		}
	}
}
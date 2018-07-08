#pragma once

CBaseEntity* CL_CreateDLLEntity(int iEnt, int iClass, int iSerialNum)
{
	ClientClass* pClient = g_pClient->GetAllClasses();
	if (!pClient)
		return false;

	while (pClient)
	{
		if (pClient->GetClassID() == iClass)
			return pClient->m_pCreateFn(iEnt, iSerialNum);
		pClient = pClient->NextClass();
	}
	return false;
}

void GloveChanger() {
	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	CEngineClient::player_info_t localPlayerInfo;
	if (!g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localPlayerInfo)) return;

	auto wearables = pLocal->GetWearables();
	static CBaseHandle glove_handle = 0;

	auto glove = reinterpret_cast<CGloves*>(g_pEntList->GetClientEntityFromHandle(wearables[0]));

	if (!glove) // There is no glove
	{
		// Try to get our last created glove
		auto our_glove = reinterpret_cast<CGloves*>(g_pEntList->GetClientEntityFromHandle(glove_handle));

		if (our_glove) // Our glove still exists
		{
			wearables[0] = glove_handle;
			glove = our_glove;
		}

		if (pLocal->GetLifeState() == LIFE_ALIVE)
		{
			// We are dead but we have a glove, destroy it
			if (glove)
			{
				glove->SetDestroyedOnRecreateEntities();
				glove->Release();
			}

			return;
		}

		if (!glove)
		{
			int iEnt = g_pEntList->GetHighestEntityIndex() + 1;
			int iSerialNumber = rand() % 0x1000;

			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)CL_CreateDLLEntity(iEnt, (int)CEconWearable, iSerialNumber);
			if (pWeapon)
			{
				auto m_Index = iEnt | (iSerialNumber << 16);
				glove_handle = m_Index;
				*(DWORD*)((DWORD)pLocal + Offsets::Player::m_hMyWearables) = m_Index;
				glove = (CGloves*)g_pEntList->GetClientEntity(iEnt);
			}

			{
				static auto set_abs_origin_fn = reinterpret_cast<void(__thiscall*)(void*, const Vector&)>
					(PatternSearch("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xE4\xF8\x51\x53\x56\x57\x8B\xF1", "xxxxxxxxxxxx", NULL, NULL));

				static const Vector new_pos = { 10000.f, 10000.f, 10000.f };

				set_abs_origin_fn(glove, new_pos);
			}
		}

		*reinterpret_cast<int*>(uintptr_t(glove) + 0x64) = -1;

		if (glove)
		{
			if (*glove->WeaponID() != 5034 || *glove->FallbackPaintKit() != 10033)
			{
				glove->SetGloveModelIndex(g_pModel->GetModelIndex("models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl"));
				*glove->WeaponID() = 5034;
				*glove->FallbackPaintKit() = 10033;
				*glove->GetEntityQuality() = 4;
				*glove->FallbackSeed() = 0;
				*glove->FallbackWear() = 0.001f;
				*glove->FallbackStatTrak() = -1;
				*glove->ItemIDHigh() = -1;
				*glove->AccountID() = localPlayerInfo.xuid;
				glove->PreDataUpdate(DATA_UPDATE_CREATED);
			}
		}
	}
}
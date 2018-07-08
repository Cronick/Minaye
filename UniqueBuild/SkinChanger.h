#pragma once
#include <unordered_map>
#define INVALID_EHANDLE_INDEX 0xFFFFFFFF
HANDLE worldmodel_handle;
CBaseCombatWeapon* worldmodel;
void SkinChanger() {
	CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());
	CEngineClient::player_info_t localPlayerInfo;
	if (!g_pEngine->GetPlayerInfo(g_pEngine->GetLocalPlayer(), &localPlayerInfo)) return;
	auto weapons = pLocal->MyWeapons();

	for (size_t i = 0; weapons[i] != INVALID_EHANDLE_INDEX; i++)
	{
		CBaseEntity *pEntity = g_pEntList->GetClientEntityFromHandle(weapons[i]);
		if (pEntity && pLocal != nullptr)
		{
			CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)pEntity;
			if (g_pCvar.getValue("misc_skinchanger") == 1)
			{
				int Model = g_pCvar.getValue("misc_skinchanger_knife");
				int Skin_T = g_pCvar.getValue("misc_skinchanger_knifeskin_t");
				int Skin_CT = g_pCvar.getValue("misc_skinchanger_knifeskin_ct");
				int Skin_T_PaintKit = 0;
				int Skin_CT_PaintKit = 0;

				if (Skin_T == 1)
				{
					Skin_T_PaintKit = 12; // Crimson Web
				}
				else if (Skin_T == 2)
				{
					Skin_T_PaintKit = 38; // Fade
				}
				else if (Skin_T == 3)
				{
					Skin_T_PaintKit = 44; // Case Hardened
				}
				else if (Skin_T == 4)
				{
					Skin_T_PaintKit = 59; // Slaughter
				}
				else if (Skin_T == 5)
				{
					Skin_T_PaintKit = 98; // Ultraviolet
				}
				else if (Skin_T == 6)
				{
					Skin_T_PaintKit = 323; // Rust Coat
				}
				else if (Skin_T == 7)
				{
					Skin_T_PaintKit = 409; // Tiger Tooth
				}
				else if (Skin_T == 8)
				{
					Skin_T_PaintKit = 413; // Marble Fade
				}
				else if (Skin_T == 9)
				{
					Skin_T_PaintKit = 414; // Rust Coat
				}
				else if (Skin_T == 10)
				{
					Skin_T_PaintKit = 415; // Doppler Ruby
				}
				else if (Skin_T == 11)
				{
					Skin_T_PaintKit = 416; // Doppler Sapphire
				}
				else if (Skin_T == 12)
				{
					Skin_T_PaintKit = 417; // Doppler Blackpearl
				}
				else if (Skin_T == 13)
				{
					Skin_T_PaintKit = 418; // Doppler Phase 1
				}
				else if (Skin_T == 14)
				{
					Skin_T_PaintKit = 419; // Doppler Phase 2
				}
				else if (Skin_T == 15)
				{
					Skin_T_PaintKit = 420; // Doppler Phase 3
				}
				else if (Skin_T == 16)
				{
					Skin_T_PaintKit = 421; // Doppler Phase 4
				}
				else if (Skin_T == 17)
				{
					Skin_T_PaintKit = 569; // Gamma Doppler Phase1
				}
				else if (Skin_T == 18)
				{
					Skin_T_PaintKit = 570; // Gamma Doppler Phase2
				}
				else if (Skin_T == 19)
				{
					Skin_T_PaintKit = 571; // Gamma Doppler Phase3
				}
				else if (Skin_T == 20)
				{
					Skin_T_PaintKit = 568; // Gamma Doppler Phase4
				}
				else if (Skin_T == 21)
				{
					Skin_T_PaintKit = 568; // Gamma Doppler Emerald
				}
				else if (Skin_T == 22)
				{
					if (Model == 0) {
						Skin_T_PaintKit = 560; // Gut knife - Lore
					}
					else if (Model == 1) {
						Skin_T_PaintKit = 559; // Flip knife - Lore
					}
					else if (Model == 2) {
						Skin_T_PaintKit = 562; // Huntsman knife - Lore
					}
					else if (Model == 3) {
						Skin_T_PaintKit = 558; // Bayonet - Lore
					}
					else if (Model == 4) {
						Skin_T_PaintKit = 562; // M9 Bayonet - Lore
					}
					else if (Model == 5) {
						Skin_T_PaintKit = 561; // Karambit - Lore
					}
				}

				if (Skin_CT == 1)
				{
					Skin_CT_PaintKit = 12; // Crimson Web
				}
				else if (Skin_CT == 2)
				{
					Skin_CT_PaintKit = 38; // Fade
				}
				else if (Skin_CT == 3)
				{
					Skin_CT_PaintKit = 44; // Case Hardened
				}
				else if (Skin_CT == 4)
				{
					Skin_CT_PaintKit = 59; // Slaughter
				}
				else if (Skin_CT == 5)
				{
					Skin_CT_PaintKit = 98; // Ultraviolet
				}
				else if (Skin_CT == 6)
				{
					Skin_CT_PaintKit = 323; // Rust Coat
				}
				else if (Skin_CT == 7)
				{
					Skin_CT_PaintKit = 409; // Tiger Tooth
				}
				else if (Skin_CT == 8)
				{
					Skin_CT_PaintKit = 413; // Marble Fade
				}
				else if (Skin_CT == 9)
				{
					Skin_CT_PaintKit = 414; // Rust Coat
				}
				else if (Skin_CT == 10)
				{
					Skin_CT_PaintKit = 415; // Doppler Ruby
				}
				else if (Skin_CT == 11)
				{
					Skin_CT_PaintKit = 416; // Doppler Sapphire
				}
				else if (Skin_CT == 12)
				{
					Skin_CT_PaintKit = 417; // Doppler Blackpearl
				}
				else if (Skin_CT == 13)
				{
					Skin_CT_PaintKit = 418; // Doppler Phase 1
				}
				else if (Skin_CT == 14)
				{
					Skin_CT_PaintKit = 419; // Doppler Phase 2
				}
				else if (Skin_CT == 15)
				{
					Skin_CT_PaintKit = 420; // Doppler Phase 3
				}
				else if (Skin_CT == 16)
				{
					Skin_CT_PaintKit = 421; // Doppler Phase 4
				}
				else if (Skin_CT == 17)
				{
					Skin_CT_PaintKit = 569; // Gamma Doppler Phase1
				}
				else if (Skin_CT == 18)
				{
					Skin_CT_PaintKit = 570; // Gamma Doppler Phase2
				}
				else if (Skin_CT == 19)
				{
					Skin_CT_PaintKit = 571; // Gamma Doppler Phase3
				}
				else if (Skin_CT == 20)
				{
					Skin_CT_PaintKit = 572; // Gamma Doppler Phase4
				}
				else if (Skin_CT == 21)
				{
					Skin_CT_PaintKit = 568; // Gamma Doppler Emerald
				}
				else if (Skin_CT == 22)
				{
					if (Model == 0) {
						Skin_CT_PaintKit = 560; // Gut knife - Lore
					}
					else if (Model == 1) {
						Skin_CT_PaintKit = 559; // Flip knife - Lore
					}
					else if (Model == 2) {
						Skin_CT_PaintKit = 562; // Huntsman knife - Lore
					}
					else if (Model == 3) {
						Skin_CT_PaintKit = 558; // Bayonet - Lore
					}
					else if (Model == 4) {
						Skin_CT_PaintKit = 562; // M9 Bayonet - Lore
					}
					else if (Model == 5) {
						Skin_CT_PaintKit = 561; // Karambit - Lore
					}
				}

				int weapon = pWeapon->GetWeaponID();
				switch (weapon)
				{
				case 1: // Deagle
					*pWeapon->FallbackPaintKit() = 37; // Blaze
					break;
				case 2: // Dual-Elites
					*pWeapon->FallbackPaintKit() = 658; // Cobra Strike
					break;
				case 3: // Five-Seven
					*pWeapon->FallbackPaintKit() = 660; // Hyper Beast
					break;
				case 4: // Glock
					*pWeapon->FallbackPaintKit() = 353; // Water Elemental
					break;
				case 7: // AK-47
					*pWeapon->FallbackPaintKit() = 675; // The Empress
					break;
				case 8: // AUG
					*pWeapon->FallbackPaintKit() = 690; // Stymphalian
					break;
				case 9: // AWP
					*pWeapon->FallbackPaintKit() = 344; // Dragon Lore	
					break;
				case 10: // FAMAS
					*pWeapon->FallbackPaintKit() = 604; // Roll Cage
					break;
				case 11: // G3SG1
					*pWeapon->FallbackPaintKit() = 511; // The Executioner
					break;
				case 13: // Galil
					*pWeapon->FallbackPaintKit() = 661; // Sugar Rush
					break;
				case 14: // M249
					*pWeapon->FallbackPaintKit() = 496; // Nebula Crusader
					break;
				case 16: // M4A4
					*pWeapon->FallbackPaintKit() = 309; // Howl
					break;
				case 17: // Mac-10
					*pWeapon->FallbackPaintKit() = 433; // Neon Rider
					break;
				case 19: // P90
					*pWeapon->FallbackPaintKit() = 156; // Death by Kitty
					break;
				case 24: // UMP45
					*pWeapon->FallbackPaintKit() = 556; // Primal Saber
					break;
				case 25: // XM1014
					*pWeapon->FallbackPaintKit() = 654; // Seasons
					break;
				case 26: // PP-Bizon
					*pWeapon->FallbackPaintKit() = 542; // Judgement of Anubis
					break;
				case 27: // MAG-7
					*pWeapon->FallbackPaintKit() = 39; // Bulldozer
					break;
				case 28: // Negev
					*pWeapon->FallbackPaintKit() = 514; // Power Loader
					break;
				case 29: // Sawed-off
					*pWeapon->FallbackPaintKit() = 256; // The Kraken
					break;
				case 30: // Tec-9
					*pWeapon->FallbackPaintKit() = 614; // Fuel Injector
					break;
				case 32: // P2000
					*pWeapon->FallbackPaintKit() = 389; // Fire Elemental
					break;
				case 33: // MP7
					*pWeapon->FallbackPaintKit() = 696; // Bloodsport
					break;
				case 34: // MP9
					*pWeapon->FallbackPaintKit() = 39; // Bulldozer
					break;
				case 35: // Nova
					*pWeapon->FallbackPaintKit() = 537; // Hyper Beast
					break;
				case 36: // P250
					*pWeapon->FallbackPaintKit() = 258; // Mehndi
					// *pWeapon->FallbackPaintKit() = 678; // See Ya Later
					break;
				case 38: // Scar20
					*pWeapon->FallbackPaintKit() = 597; // Bloodsport
					break;
				case 39: // SG 553
					*pWeapon->FallbackPaintKit() = 487; // Cyrex
					break;
				case 40: // SSG08
					*pWeapon->FallbackPaintKit() = 624; // Dragonfire
					break;
				case 60: // M4A1-SILENCER
					*pWeapon->FallbackPaintKit() = 497; // Golden Coil
					break;
				case 61: // USP-SILENCER
					*pWeapon->FallbackPaintKit() = 504; // Kill Confirmed
					break;
				case 63: // CZ75A
					*pWeapon->FallbackPaintKit() = 643; // Xiangliu
					break;
				case 64: // Revolver
					*pWeapon->FallbackPaintKit() = 683; // Llama Cannon
					break;
				default:
					break;
				}
				*pWeapon->FallbackSeed() = 1;
				// #############################################################################################
				if (pEntity->GetClientClass()->GetClassID() == (int)ClassIDs::CKnife) {
					worldmodel_handle = pWeapon->WeaponWorldModel();
					//if (worldmodel_handle) worldmodel = (CBaseCombatWeapon*)g_pEntList->GetClientEntityFromHandle(worldmodel_handle);
					if (Model == 0) {
						int iGut = g_pModel->GetModelIndex("models/weapons/v_knife_gut.mdl");
						*pWeapon->ModelIndex() = iGut;
						*pWeapon->ViewModelIndex() = iGut;
						//if (worldmodel) *worldmodel->ModelIndex() = iGut + 1;
						*pWeapon->WeaponID() = 506;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
					else if (Model == 1) {
						int iFlip = g_pModel->GetModelIndex("models/weapons/v_knife_flip.mdl");
						*pWeapon->ModelIndex() = iFlip;
						*pWeapon->ViewModelIndex() = iFlip;
						//if (worldmodel) *worldmodel->ModelIndex() = iFlip + 1;
						*pWeapon->WeaponID() = 505;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
					else if (Model == 2) {
						int iHuntsman = g_pModel->GetModelIndex("models/weapons/v_knife_tactical.mdl");
						*pWeapon->ModelIndex() = iHuntsman;
						*pWeapon->ViewModelIndex() = iHuntsman;
						//if (worldmodel) *worldmodel->ModelIndex() = iHuntsman + 1;
						*pWeapon->WeaponID() = 509;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
					else if (Model == 3) {
						int iBayonet = g_pModel->GetModelIndex("models/weapons/v_knife_bayonet.mdl");
						*pWeapon->ModelIndex() = iBayonet;
						*pWeapon->ViewModelIndex() = iBayonet;
						//if (worldmodel) *worldmodel->ModelIndex() = iBayonet + 1;
						*pWeapon->WeaponID() = 500;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
					else if (Model == 4) {
						int iM9Bayonet = g_pModel->GetModelIndex("models/weapons/v_knife_m9_bay.mdl");
						*pWeapon->ModelIndex() = iM9Bayonet;
						*pWeapon->ViewModelIndex() = iM9Bayonet;
						//if (worldmodel) *worldmodel->ModelIndex() = iM9Bayonet + 1;
						*pWeapon->WeaponID() = 508;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
					else if (Model == 5) {
						int iKarambit = g_pModel->GetModelIndex("models/weapons/v_knife_karam.mdl");
						*pWeapon->ModelIndex() = iKarambit;
						*pWeapon->ViewModelIndex() = iKarambit;
						//if (worldmodel) *worldmodel->ModelIndex() = iKarambit + 1;
						*pWeapon->WeaponID() = 507;
						*pWeapon->GetEntityQuality() = 3;
						if (pLocal->GetTeamNumber() == 2) {
							*pWeapon->FallbackPaintKit() = Skin_T_PaintKit; // T
							if (Skin_T_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
						else {
							*pWeapon->FallbackPaintKit() = Skin_CT_PaintKit; // CT
							if (Skin_CT_PaintKit == 44) {
								*pWeapon->FallbackSeed() = 442; // Blue gem - 96%
							}
						}
					}
				}
				// #############################################################################################
				*pWeapon->OwnerXuidLow() = 0;
				*pWeapon->OwnerXuidHigh() = 0;
				*pWeapon->FallbackWear() = 0.001f;
				if (!pWeapon->IsOther()) {
					*pWeapon->FallbackStatTrak() = 1337;
				}
				*pWeapon->AccountID() = localPlayerInfo.xuid;
				*pWeapon->ItemIDHigh() = -1;
			}
		}
	}
}
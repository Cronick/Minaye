#include "FrameStageNotify.h"
#include "SkinChanger.h"
//#include "GloveChanger.h"
#include "ItemDefinitions.h"

using FrameStageNotifyFn = void(__stdcall*)(ClientFrameStage_t);
extern FrameStageNotifyFn oFrameStageNotify;
FrameStageNotifyFn oFrameStageNotify;

typedef void(__stdcall *fsn_t)(ClientFrameStage_t);
void __stdcall FrameStageNotifyHook(ClientFrameStage_t stage)
{
	if (stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START) {
		if (g_pCvar.getValue("misc_skinchanger") == 1) {
			//GloveChanger();
			SkinChanger();

			// Get pLocal
			CBaseEntity* pLocal = g_pEntList->GetClientEntity(g_pEngine->GetLocalPlayer());

			// Get a handle to the view model entity.
			CBaseHandle viewmodel_handle = pLocal->ViewModel();

			if (viewmodel_handle == INVALID_EHANDLE_INDEX)
				return;

			// Convert the view model handle into an entity pointer.
			CBaseViewModel* viewmodel = static_cast<CBaseViewModel*>(g_pEntList->GetClientEntityFromHandle(viewmodel_handle));

			if (!viewmodel)
				return;

			// Get a handle to the active weapon for this view model.
			CBaseHandle viewmodel_weapon_handle = viewmodel->GetWeapon();

			if (viewmodel_weapon_handle == INVALID_EHANDLE_INDEX)
				return;

			// Convert the view model weapon handle into an entity pointer.
			CBaseCombatWeapon* viewmodel_weapon = static_cast<CBaseCombatWeapon*>(g_pEntList->GetClientEntityFromHandle(viewmodel_weapon_handle));

			if (!viewmodel_weapon)
				return;

			// Finally, write the correct model index for this weapon.
			if (ItemDefinitionIndex.find(*viewmodel_weapon->WeaponID()) != ItemDefinitionIndex.end()) {
				const Item_t& override_weapon = ItemDefinitionIndex.at(*viewmodel_weapon->WeaponID());
				*viewmodel->GetWeaponModelIndex() = g_pModel->GetModelIndex(override_weapon.model);
			}
		}
	}
	g_phkFrameStageNotify->GetMethod<fsn_t>(36)(stage);
}
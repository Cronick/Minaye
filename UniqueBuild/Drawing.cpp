#include "Drawing.h"

CDraw g_pDraw;

void CDraw::init()
{
	if (g_pSurface == NULL)
	{
		MessageBox(0, "Surface Problems", "Hook", 0);
		return;
	}

	font_menuarrows = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Visitor TT2 BRK", 12, 200, 0, 0, FONTFLAG_ANTIALIAS + FONTFLAG_OUTLINE);
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Microsoft Sans Serif", 12, 700, 0, 0, FONTFLAG_OUTLINE);
	g_pSurface->SetFontGlyphSet(font_menuarrows, "Segoe UI", 17, 100, 0, 0, FONTFLAG_ANTIALIAS);

	font_money = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Visitor TT2 BRK", 12, 200, 0, 0, FONTFLAG_ANTIALIAS + FONTFLAG_OUTLINE);
	//g_pSurface->SetFontGlyphSet(font_menuarrows, "Microsoft Sans Serif", 12, 700, 0, 0, FONTFLAG_OUTLINE);
	g_pSurface->SetFontGlyphSet(font_money, "Consolas", 20, 100, 0, 0, FONTFLAG_ANTIALIAS);


	esp_font = g_pSurface->CreateFont();
	// g_pSurface->SetFontGlyphSet(font_menuarrows, "Visitor TT2 BRK", 11, 200, 0, 0, FONTFLAG_ANTIALIAS + FONTFLAG_OUTLINE);
	// g_pSurface->SetFontGlyphSet(esp_font, "Microsoft Sans Serif", 12, 700, 0, 0, FONTFLAG_OUTLINE);
	g_pSurface->SetFontGlyphSet(esp_font, "Consolas", 12, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	

	font_menuoptions = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menuoptions, "Segoe UI", 17, 100, 0, 0, FONTFLAG_ANTIALIAS);
	//g_pSurface->SetFontGlyphSet(font_menuoptions, "Razer Regular Italic", 14, 525, 0, 0, FONTFLAG_ANTIALIAS);

	font_menutitle = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_menutitle, "Razer Regular Italic", 21, 200, 0, 0, 0x200);
	g_pSurface->SetFontGlyphSet(font_menutitle, "Segoe UI", 13, 200, 0, 0, FONTFLAG_ANTIALIAS);

	font_menutab = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menutab, "Razer Regular Italic", 15, 200, 0, 0, FONTFLAG_ANTIALIAS);

	font_menu = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(font_menu, "Razer Regular Italic", 13, 200, 0, 0, FONTFLAG_ANTIALIAS);

	menu_title = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_title, "Verdana", 18, 1, 0, 0, FONTFLAG_ANTIALIAS);

	menu_ready = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_ready, "Verdana", 13, 1, 0, 0, FONTFLAG_ANTIALIAS);

	menu_webdings = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_webdings, "Arial", 22, 100, 0, 0, FONTFLAG_ANTIALIAS);

	menu_tabs = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(menu_tabs, "Razer Regular Italic", 21, 200, 0, 0, 0x200);
	g_pSurface->SetFontGlyphSet(menu_tabs, "Verdana", 13, 20, 0, 0, FONTFLAG_ANTIALIAS);

	menu_features = g_pSurface->CreateFont();
	g_pSurface->SetFontGlyphSet(menu_features, "Arial", 22, 100, 0, 0, FONTFLAG_ANTIALIAS);

	font_esp = g_pSurface->CreateFont();
	//g_pSurface->SetFontGlyphSet(font_esp, "Razer Regular Italic", 13, 200, 0, 0, FONTFLAG_OUTLINE + FONTFLAG_NONE);
	g_pSurface->SetFontGlyphSet(font_esp, "Visitor TT2 BRK", 9, 200, 0, 0, FONTFLAG_OUTLINE + FONTFLAG_NONE);

}

void CDraw::DrawOutlineRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDraw::FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void CDraw::LineRGBA(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawLine(x1, y1, x2, y2);
}

void CDraw::DrawRect(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	g_pSurface->DrawSetColor(r, g, b, a);
	g_pSurface->DrawFilledRect(x1, y1, x2, y2);
}

void CDraw::DrawHealthBar(int x, int y, int w, int h, int r, int g, int b, int a, float health)
{
	x -= w / 2;
	y -= h / 2;
	g_pDraw.FillRGBA(x, y, w, h + 1, 0, 0, 0, 255);
	UINT hw = (UINT)(((h + 1) * health) / 100);
	g_pDraw.FillRGBA(x + 1, y + 1, w - 2, hw - 2, r, g, b, a);
}

void CDraw::DrawEspBox(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pDraw.DrawOutlineRect(x - 1, y - 1, w + 2, h + 2, 0, 0, 0, a);
	g_pDraw.DrawOutlineRect(x + 1, y + 1, w - 2, h - 2, 0, 0, 0, a);
	g_pDraw.DrawOutlineRect(x, y, w, h, r, g, b, a);
}

int CDraw::getWidth(unsigned long font, const char* input, ...)
{
	INT iWide = 0;
	INT iTall = 0;
	INT iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

	wchar_t* pszUnicode = new wchar_t[iBufSize];
	MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

	g_pSurface->GetTextSize(font, pszUnicode, iWide, iTall);

	delete[] pszUnicode;

	return iWide;
}

std::wstring CDraw::stringToWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

void CDraw::DrawMinimizeWindow(int x, int y, int w, int h, int r, int g, int b, int a, int r1, int g1, int b1, int a1)
{
	DrawOutlineRect(x, y, w, h, r, g, b, a);
	FillRGBA(x - 3, y + 3, w, h, r1, g1, b1, a1);
	FillRGBA(x, y + 1, w, 1, r, g, b, a);

	DrawOutlineRect(x - 3, y + 3, w, h, r, g, b, a);
	FillRGBA(x - 3, y + 4, w, 1, r, g, b, a);
}

void CDraw::VSLogo(int x, int y, int w, int h, int r, int g, int b, int a)
{
	FillRGBA(x, y + h / 4, 2, h - h / 2, r, g, b, a);

	FillRGBA(x + w, y, 3, h, r, g, b, a);

	LineRGBA(x + w, y, x, y + h / (float)1.3, r, g, b, a);
	LineRGBA(x + w + 1, y, x + 1, y + h / (float)1.3, r, g, b, a);
	LineRGBA(x + w + 2, y, x + 2, y + h / (float)1.3, r, g, b, a);

	LineRGBA(x, y + h / 4, x + w, y + h, r, g, b, a);
	LineRGBA(x + 1, y + h / 4, x + w + 1, y + h, r, g, b, a);
	LineRGBA(x + 2, y + h / 4, x + w + 2, y + h, r, g, b, a);
}

void CDraw::DrawString(unsigned long Font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	CHAR szBuffer[MAX_PATH];

	if (!input)
		return;

	vsprintf(szBuffer, input, (char*)&input + _INTSIZEOF(input));

	if (center)
		x -= getWidth(Font, szBuffer) / 2;

	g_pSurface->DrawSetTextColor(r, g, b, a);
	g_pSurface->DrawSetTextFont(Font);
	g_pSurface->DrawSetTextPos(x, y);

	std::wstring wide = stringToWide(std::string(szBuffer));
	g_pSurface->DrawPrintText(wide.c_str(), wide.length());
}

RECT CDraw::GetViewport()
{
	RECT Viewport = { 0, 0, 0, 0 };
	int w, h;
	g_pEngine->GetScreenSize(w, h);
	Viewport.right = w; Viewport.bottom = h;
	return Viewport;
}

bool CDraw::WorldToScreen(Vector &in, Vector &out)
{
	const matrix3x4& worldToScreen = g_pEngine->WorldToScreenMatrix(); //Grab the world to screen matrix from CEngineClient::WorldToScreenMatrix

	float w = worldToScreen[3][0] * in[0] + worldToScreen[3][1] * in[1] + worldToScreen[3][2] * in[2] + worldToScreen[3][3]; //Calculate the angle in compareson to the player's camera.
	out.z = 0; //Screen doesn't have a 3rd dimension.

	if (w > 0.001) //If the object is within view.
	{
		RECT ScreenSize = GetViewport();
		float fl1DBw = 1 / w; //Divide 1 by the angle.
		out.x = (ScreenSize.right / 2) + (0.5f * ((worldToScreen[0][0] * in[0] + worldToScreen[0][1] * in[1] + worldToScreen[0][2] * in[2] + worldToScreen[0][3]) * fl1DBw) * ScreenSize.right + 0.5f); //Get the X dimension and push it in to the Vector.
		out.y = (ScreenSize.bottom / 2) - (0.5f * ((worldToScreen[1][0] * in[0] + worldToScreen[1][1] * in[1] + worldToScreen[1][2] * in[2] + worldToScreen[1][3]) * fl1DBw) * ScreenSize.bottom + 0.5f); //Get the Y dimension and push it in to the Vector.
		return true;
	}

	return false;
}

void CDraw::DrawBone(CBaseEntity* pEntity, int pEntityIndex, int a)
{
	studiohdr_t* pStudioHdr = g_pModel->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{

			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			int iChestBone = 6;  // Parameter of relevant Bone number
			Vector vBreastBone; // New reference Point for connecting many bones
			Vector vUpperDirection = pEntity->GetBonePos(iChestBone + 1) - pEntity->GetBonePos(iChestBone); // direction vector from chest to neck
			vBreastBone = pEntity->GetBonePos(iChestBone) + vUpperDirection / 2;
			Vector vDeltaChild = vChild - vBreastBone; // Used to determine close bones to the reference point
			Vector vDeltaParent = vParent - vBreastBone;

			// Eliminating / Converting all disturbing bone positions in three steps.
			if ((vDeltaParent.Length() < 9 && vDeltaChild.Length() < 9))
				vParent = vBreastBone;

			if (j == iChestBone - 1)
				vChild = vBreastBone;

			if (abs(vDeltaChild.z) < 5 && (vDeltaParent.Length() < 5 && vDeltaChild.Length() < 5) || j == iChestBone)
				continue;


			if (g_pDraw.WorldToScreen(vParent, sParent) && g_pDraw.WorldToScreen(vChild, sChild)) {
				g_pDraw.LineRGBA(sParent.x, sParent.y, sChild.x, sChild.y, 255, 255, 255, a);
			}
		}
	}
}
#include "render.h"

#include "../sdk/interfaces.h"

namespace render {

	unsigned long font;
	unsigned long icons;
	unsigned long fontLight;
	unsigned long fontBigger;

	void init() {

		VMProtectBeginMutation("render::init");

		font = interfaces::surface->CreateFont(); //Tahoma//
		fontBigger = interfaces::surface->CreateFont(); //Tahoma//
		icons = interfaces::surface->CreateFont(); //Tahoma//
		fontLight = interfaces::surface->CreateFont(); //Tahoma//

		interfaces::surface->SetFontGlyphSet(font, XorStr("Visitor TT2 BRK"), 12, 400, 0, 0, FontFlags_t::FONTFLAG_OUTLINE);
		interfaces::surface->SetFontGlyphSet(icons, XorStr("csgo_icons"), 22, 400, 0, 0, FontFlags_t::FONTFLAG_NONE);
		interfaces::surface->SetFontGlyphSet(fontLight, XorStr("Tahoma"), 12, 400, 0, 0, FontFlags_t::FONTFLAG_OUTLINE);
		interfaces::surface->SetFontGlyphSet(fontBigger, XorStr("Tahoma"), 20, 400, 0, 0, FontFlags_t::FONTFLAG_OUTLINE);
			
		VMProtectEnd();
	}

	void drawEntityBox(Entity* entity, Color c) {

		VMProtectBeginMutation("render::drawEntityBox");

		box box;

		if (!utils::getEntityBox(entity, box))
			return;

		drawOutlinedBox(box.x,box.y,box.w,box.h,c);

		VMProtectEnd();
	}

	void drawCircle(int x, int y, int r, int s, Color color) {

		VMProtectBeginMutation("render::drawCircle");

		float Step = M_PI * 2.0 / s;

		for (float a = 0; a < (M_PI*2.0); a += Step) {
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a + Step) + x;
			float y2 = r * sin(a + Step) + y;
			interfaces::surface->DrawSetColor(color);
			interfaces::surface->DrawLine(x1, y1, x2, y2);
		}

		VMProtectEnd();
	}

	void drawLine(int x1, int y1, int x2, int y2, Color color) {

		VMProtectBeginMutation("render::drawLine");

		interfaces::surface->DrawSetColor(color);
		interfaces::surface->DrawLine(x1, y1, x2, y2);

		VMProtectEnd();
	}

	void drawOutlinedBoxFilled(int x, int y, int sizeX, int sizeY, Color color) {

		VMProtectBeginMutation("render::drawOutlinedBoxFilled");

		drawOutlinedRectangle(x - 1, y - 1, sizeX + 2, sizeY + 2, Color(0, 0, 0, color.a()));
		drawOutlinedRectangle(x + 1, y + 1, sizeX - 2, sizeY - 2, Color(0, 0, 0, color.a()));
		drawRectangle(x, y, sizeX, sizeY, color);

		VMProtectEnd();
	}

	void drawOutlinedBox(int x, int y, int sizeX, int sizeY, Color color) {

		VMProtectBeginMutation("render::drawOutlinedBox");

		drawOutlinedRectangle(x - 1, y - 1, sizeX + 2, sizeY + 2, Color(0, 0, 0, color.a()));
		drawOutlinedRectangle(x + 1, y + 1, sizeX - 2, sizeY - 2, Color(0, 0, 0, color.a()));
		drawOutlinedRectangle(x, y, sizeX, sizeY, color);

		VMProtectEnd();
	}

	void drawText(int x, int y, unsigned long font, std::string string, bool text_centered, Color color) {

		VMProtectBeginMutation("render::drawText");

		std::wstring text = std::wstring(string.begin(), string.end());

		const wchar_t* converted_text = text.c_str();

		int width, height;
		interfaces::surface->GetTextSize(font, converted_text, width, height);

		interfaces::surface->DrawSetTextColor(color);
		interfaces::surface->DrawSetTextFont(font);

		if (text_centered)
			interfaces::surface->DrawSetTextPos(x - (width / 2), y);
		else
			interfaces::surface->DrawSetTextPos(x, y);

		interfaces::surface->DrawPrintText(converted_text, wcslen(converted_text));

		VMProtectEnd();
	}

	void drawRectangle(int x, int y, int sizeX, int sizeY, Color color) {

		VMProtectBeginMutation("render::drawRectangle");

		interfaces::surface->DrawSetColor(color);
		interfaces::surface->DrawFilledRect(x, y, x + sizeX, y + sizeY);

		VMProtectEnd();
	}

	void drawOutlinedRectangle(int x, int y, int sizeX, int sizeY, Color color) {

		VMProtectBeginMutation("render::drawOutlinedRectangle");

		interfaces::surface->DrawSetColor(color);
		interfaces::surface->DrawOutlinedRect(x, y, x + sizeX, y + sizeY);

		VMProtectEnd();
	}

	void drawGradiant(int x, int y, int sizeX, int sizeY, Color color1, Color color2, int alpha, bool horizontal) {

		VMProtectBeginMutation("render::drawGradiant");

		interfaces::surface->DrawSetColor(color1);
		interfaces::surface->DrawFilledRectFade(x, y, x + sizeX, y + sizeY, alpha, alpha, horizontal);

		interfaces::surface->DrawSetColor(color2);
		interfaces::surface->DrawFilledRectFade(x, y, x + sizeX, y + sizeY, 0, alpha, horizontal);

		VMProtectEnd();
	}
}
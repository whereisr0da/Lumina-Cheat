#pragma once

#define FGUI_IMPLEMENTATION

#include "../../sdk/interfaces.h"
#include "../render.h"

#include "../zgui/dist/zgui.hh"

//#include "../fgui_old/FGUI.hh"

void line(int x, int y, int x2, int y2, zgui::color c) noexcept
{
	interfaces::surface->DrawSetColor(c.r, c.g, c.b, c.a);
	interfaces::surface->DrawLine(x, y, x+x2, y+y2);
}

void rect(int x, int y, int x2, int y2, zgui::color c) noexcept
{
	render::drawOutlinedRectangle(x, y, x2, y2, Color(c.r, c.g, c.b, c.a));
}

void filled_rect(int x, int y, int x2, int y2, zgui::color c) noexcept
{
	render::drawRectangle(x, y, x2, y2, Color(c.r, c.g, c.b, c.a));
}

void text(int x, int y, zgui::color color, int font, bool center, const char* text) noexcept
{
	render::drawText(x, y, font, text, false, Color(color.r, color.g, color.b, color.a));
}

void get_text_size(unsigned long font, const char* text, int& width, int& height) noexcept
{
	interfaces::surface->GetTextSize(font, (wchar_t*)text, width, height);
}

float get_frametime() noexcept
{
	return interfaces::globals->frametime;
}

void zguiInit() {

	zgui::functions.draw_line = line;
	zgui::functions.draw_rect = rect;
	zgui::functions.draw_filled_rect = filled_rect;
	zgui::functions.draw_text = text;
	zgui::functions.get_text_size = get_text_size;
	zgui::functions.get_frametime = get_frametime;
}

/*
void create_font(fgui::font& font, const std::string_view family, const std::int32_t size, const std::int32_t flags, const bool bold) {

	font = interfaces::surface->CreateFont();

	interfaces::surface->SetFontGlyphSet(font, family.data(), size, bold ? 800 : 0, 0, 0, flags, 0, 0);
}

void get_screen_size(std::int32_t& x, std::int32_t& y) {
	interfaces::surface->GetScreenSize(x, y);
}

fgui::dimension get_text_size(const fgui::font& font, const std::string_view text) {
	fgui::dimension dimension = { 0, 0 };

	interfaces::surface->GetTextSize(font, std::wstring(text.begin(), text.end()).data(), dimension.width, dimension.height);

	return dimension;
}

void rectangle(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h, const fgui::color color) {
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawFilledRect(x, y, x + w, y + h);
}

void outlined_rectangle(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h, const fgui::color color) {
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void line(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h, const fgui::color color) {
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawLine(x, y, w, h);
}

void polygon(const std::int32_t count, fgui::vertex* vertex, const fgui::color color) {

	

	static auto texture = interfaces::surface->CreateNewTextureID(true);

	std::uint8_t buffer[4] = { 255, 255, 255, 255 };

	Vertex_t* vec = new Vertex_t(,);

	interfaces::surface->DrawSetTextureRGBA(texture, buffer, 1, 1);
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawSetTexture(texture);
	interfaces::surface->DrawTexturedPolygon(count, vec, true);*
}

void text(const std::int32_t x, const std::int32_t y, const fgui::color color, const unsigned long font, const std::string_view text) {
	const auto converted_text = std::wstring(text.begin(), text.end());

	interfaces::surface->DrawSetTextColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawSetTextFont(font);
	interfaces::surface->DrawSetTextPos(x, y);
	interfaces::surface->DrawPrintText(converted_text.c_str(), std::wcslen(converted_text.c_str()));
}

void circle(const std::int32_t x, const std::int32_t y, const std::int32_t radius, const std::int32_t segments, const fgui::color color) {
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawOutlinedCircle(x, y, radius, segments);
}

void gradient(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h, const std::int32_t first_alpha, const std::int32_t second_alpha, const fgui::color color, const bool horizontal) {
	interfaces::surface->DrawSetColor(color.m_red, color.m_green, color.m_blue, color.m_alpha);
	interfaces::surface->DrawFilledRectFade(x, y, x + w, y + h, first_alpha, second_alpha, horizontal);
}

void colored_gradient(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h, const fgui::color first_color, const fgui::color second_color, const bool is_horizontal) {
	if (is_horizontal) {
		rectangle(x, y, w, h, first_color);

		for (auto i = 0; i < w; i++)
			rectangle(x + i, y, 1, h, fgui::color(second_color.m_red, second_color.m_red, second_color.m_blue, i / w * 255));
	}
	else {
		rectangle(x, y, w, h, first_color);

		for (auto i = 0; i < w; i++)
			rectangle(x, y + i, w, 1, fgui::color(second_color.m_red, second_color.m_red, second_color.m_blue, i / w * 255));
	}
}

void get_alpha_value(const std::int32_t x, const std::int32_t y, const std::int32_t w, const std::int32_t h) {
	for (auto i = 0; i < h / 5; i++) {
		for (auto t = 0; t < w / 5; t++) {
			const auto pixel = static_cast<std::int32_t>(std::roundf(t));
			const auto line = static_cast<std::int32_t>(std::roundf(i));
			const auto is_brick_light = line % 2 ? pixel % 2 : pixel % 2 == 0;
			const auto new_color = is_brick_light ? fgui::color(60, 60, 60) : fgui::color(40, 40, 40);

			rectangle(x + t * 5, y + i * 5, 5, 5, new_color);
		}
	}
}

void clip_rectangle(const std::int32_t x, const std::int32_t y, const std::int32_t width, const std::int32_t height) {
	
	const fgui::rect viewport = { x, y, (x + width), (y + height) };

	//interfaces::surface->set_clip_rectangle(viewport.left, viewport.top, viewport.right, viewport.bottom);
}

void setup_render_funcs() {
	fgui::render.create_font = create_font;
	fgui::render.get_screen_size = get_screen_size;
	fgui::render.get_text_size = get_text_size;
	fgui::render.rect = rectangle;
	fgui::render.gradient = gradient;
	fgui::render.colored_gradient = colored_gradient;
	fgui::render.outline = outlined_rectangle;
	fgui::render.line = line;
	fgui::render.polygon = polygon;
	fgui::render.circle = circle;
	fgui::render.text = text;
	fgui::render.alpha = get_alpha_value;
	fgui::render.clip_rect = clip_rectangle;

	//fonts.push_back(CONV_ENUM_TYPE(std::int32_t, enums::font::font_watermark));
	//fonts.push_back(CONV_ENUM_TYPE(std::int32_t, enums::font::font_visuals));

	//fgui::render.create_font(, "Tahoma", 12, fgui::external::font_flags::SHADOW, false);
	//fgui::render.create_font(, "Tahoma", 16, fgui::external::font_flags::SHADOW, false);
}*/

/*
#include "FGUI.hpp"



// NOTE: make sure to use your surface interface pointer
// replace "interfaces::surface" with your pointer


namespace FGUI_SURFACE
{
	inline void CreateFont(FGUI::FONT& _font, std::string _family, int _size, int _flags, bool _bold)
	{
		_font = interfaces::surface->CreateFont();
		interfaces::surface->SetFontGlyphSet(_font, _family.c_str(), _size, _bold ? 800 : 0, 0, 0, _flags);
	}

	inline FGUI::DIMENSION GetScreenSize()
	{
		static FGUI::DIMENSION dmTemporarySize = { 0, 0 };

		interfaces::surface->GetScreenSize(dmTemporarySize.m_iWidth, dmTemporarySize.m_iHeight);

		return dmTemporarySize;
	}

	inline FGUI::DIMENSION GetTextSize(FGUI::FONT _font, std::string _text)
	{
		static FGUI::DIMENSION dmTemporarySize = { 0, 0 };

		interfaces::surface->GetTextSize(_font, std::wstring(_text.begin(), _text.end()).c_str(), dmTemporarySize.m_iWidth, dmTemporarySize.m_iHeight);

		return dmTemporarySize;
	}

	inline void Rectangle(int _x, int _y, int _width, int _height, FGUI::COLOR _color)
	{
		interfaces::surface->DrawSetColor(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);
		interfaces::surface->DrawFilledRect(_x, _y, _x + _width, _y + _height);
	}

	inline void Outline(int _x, int _y, int _width, int _height, FGUI::COLOR _color)
	{
		interfaces::surface->DrawSetColor(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);
		interfaces::surface->DrawOutlinedRect(_x, _y, _x + _width, _y + _height);
	}

	inline void Gradient(int _x, int _y, int _width, int _height, FGUI::COLOR _color1, FGUI::COLOR _color2, bool _horizontal)
	{
		interfaces::surface->DrawSetColor(_color1.m_ucRed, _color1.m_ucGreen, _color1.m_ucBlue, _color1.m_ucAlpha);
		interfaces::surface->DrawFilledRectFade(_x, _y, _x + _width, _y + _height, 255, 255, _horizontal);

		interfaces::surface->DrawSetColor(_color2.m_ucRed, _color2.m_ucGreen, _color2.m_ucBlue, _color2.m_ucAlpha);
		interfaces::surface->DrawFilledRectFade(_x, _y, _x + _width, _y + _height, 0, 255, _horizontal);
	}

	inline void Line(int _from_x, int _from_y, int _to_x, int _to_y, FGUI::COLOR _color)
	{
		interfaces::surface->DrawSetColor(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha);
		interfaces::surface->DrawLine(_from_x, _from_y, _to_x, _to_y);
	}

	inline void Text(int _x, int _y, FGUI::FONT _font, FGUI::COLOR _color, std::string _text)
	{
		render::drawText(_x, _y, _font, _text, false, Color(_color.m_ucRed, _color.m_ucGreen, _color.m_ucBlue, _color.m_ucAlpha));
	}

	// NOTE: call this function only once (preferably when you initialize your application)
	inline void init()
	{
		FGUI::RENDER.CreateFont = FGUI_SURFACE::CreateFont;
		FGUI::RENDER.GetScreenSize = FGUI_SURFACE::GetScreenSize;
		FGUI::RENDER.GetTextSize = FGUI_SURFACE::GetTextSize;
		FGUI::RENDER.Rectangle = FGUI_SURFACE::Rectangle;
		FGUI::RENDER.Outline = FGUI_SURFACE::Outline;
		FGUI::RENDER.Line = FGUI_SURFACE::Line;
		FGUI::RENDER.Text = FGUI_SURFACE::Text;
		FGUI::RENDER.Gradient = FGUI_SURFACE::Gradient;
	}
}
*/
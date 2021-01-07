#ifndef render_h

#define render_h

#include "../common/includes.h"

namespace render {

	extern unsigned long font;

	extern unsigned long icons;

	extern unsigned long fontLight;

	extern unsigned long fontBigger;

	void init();

	void drawLine(int x1, int y1, int x2, int y2, Color color);

	void drawText(int x, int y, unsigned long font, std::string string, bool text_centered, Color color);

	void drawEntityBox(Entity* entity, Color c);

	void drawOutlinedBox(int x, int y, int sizeX, int sizeY, Color color);

	void drawOutlinedBoxFilled(int x, int y, int sizeX, int sizeY, Color color);

	void drawOutlinedRectangle(int x, int y, int sizeX, int sizeY, Color color);

	void drawRectangle(int x, int y, int sizeX, int sizeY, Color color);

	void drawCircle(int x, int y, int r, int s, Color color);

	void drawGradiant(int x, int y, int sizeX, int sizeY, Color color1, Color color2, int alpha, bool horizontal);
}

#endif
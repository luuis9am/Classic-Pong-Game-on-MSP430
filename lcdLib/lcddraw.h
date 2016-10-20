#ifndef lcddraw_included
#define lcddraw_included

void drawPixel(u_char x, u_char y, u_int color);
void fillRectangle(u_char xMin, u_char yMin, u_char width, u_char height, u_int color);
void clearScreen(u_int color);

void drawString5x7(u_char x, u_char y, char *string, u_int fgColor, u_int bgColor);
void drawChar5x7(u_char x, u_char y, char c, u_int fgColor, u_int bgColor);

void drawRectOutline(u_char xMin, u_char yMin, u_char width, u_char height,
		     u_int color);
void computeChordVec(u_char chordVec[], u_char radius);

#endif // included



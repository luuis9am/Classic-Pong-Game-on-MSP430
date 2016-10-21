#ifndef lcddraw_included
#define lcddraw_included

void drawPixel(u_char x, u_char y, u_int colorRGB);
void fillRectangle(u_char xMin, u_char yMin, u_char width, u_char height, u_int colorRGB);
void clearScreen(u_int colorRGB);

void drawString5x7(u_char x, u_char y, char *string, u_int fgColorRGB, u_int bgColorRGB);
void drawChar5x7(u_char x, u_char y, char c, u_int fgColorRGB, u_int bgColorRGB);

void drawRectOutline(u_char xMin, u_char yMin, u_char width, u_char height,
		     u_int colorRGB);
void computeChordVec(u_char chordVec[], u_char radius);

#endif // included



#ifndef lcddraw_included
#define lcddraw_included

void drawPixel(u_char col, u_char row, u_int colorBGR);
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, u_int colorBGR);
void clearScreen(u_int colorBGR);

void drawString5x7(u_char col, u_char row, char *string, 
		   u_int fgColorBGR, u_int bgColorBGR);
void drawChar5x7(u_char col, u_char row, char c, 
		 u_int fgColorBGR, u_int bgColorBGR);

void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR);
#endif // included



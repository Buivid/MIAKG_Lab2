#include "draw.h"

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  // assert(NULL != surface);
  // assert(x < SCREEN_WIDTH);
  // assert(y < SCREEN_HEIGHT);

  if((x > 0 && x < SCREEN_WIDTH) && (y > 0 && y < SCREEN_HEIGHT))
  {
  Uint32 *pixels = (Uint32 *)surface->pixels;
  pixels[(y * surface->w) + x] = pixel;
  }
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
  assert(NULL != surface);
  assert(x < SCREEN_WIDTH);
  assert(y < SCREEN_HEIGHT);

  Uint32 *pixels = (Uint32 *)surface->pixels;
  return pixels[(y * surface->w) + x];
}

void line (SDL_Surface *s, int x1, int y1, int x2, int y2, int color)
{
 int dx = abs ( x2 - x1 );
 int dy = abs ( y2 - y1 );
 int sx = x2 >= x1 ? 1 : -1;
 int sy = y2 >= y1 ? 1 : -1;

 if ( dy <= dx ) {
 int d = ( dy << 1 ) - dx;
 int d1 = dy << 1;
 int d2 = (dy-dx)<<1;
 put_pixel32( s, x1, y1, color);
 for (int x=x1 +sx, y=y1, i=1; i <= dx; i++, x+=sx) {
 if (d > 0 ) {
 d += d2; y += sy;
 }
 else
 d+=d1;
 put_pixel32( s, x, y, color);
 }
 }
 else {
 int d = ( dx << 1 ) - dy;
 int d1 = dx << 1;
 int d2 = (dx-dy)<<1;

 put_pixel32(s, x1, y1, color);
 for (int x=x1, y=y1+sy, i=1; i <= dy; i++, y+=sy) {
 if ( d > 0 ) {
 d += d2; x += sx;
 }
 else
 d +=d1;
 put_pixel32(s, x, y, color);
 }
 }
}

void draw(SDL_Surface *s, Figure square, int n)
{

  square.transform();
  square.draw(s);
  square.nested_figure(s, n);
  // for(int i=0; i<4; i++)
  // {
  //   // if(i==3)
  //   // {
  //   //   p[i]=square[i];
  //   //   p[0]=square[0];
  //   //   line(s, p[i].x, p[i].y, p[0].x, p[0].y, RGB32(0, 255, 0));
  //   // }
  //   // else
  //   // {
  //   // p[i]=square[i];
  //   // p[i+1]=square[i+1];
  //   // line(s, p[i].x, p[i].y, p[i+1].x, p[i+1].y, RGB32(0, 255, 0));
  //   // }
  // }

  // или использу¤ макрос можно получить код цвета:
  //   RGB32(0, 255, 0) эквивалентно записи 0x0000FF00
}

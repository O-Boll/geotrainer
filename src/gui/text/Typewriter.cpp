/*----------------------------------------------------------------------------
This file is part of GeoTrainer.

MIT License

Copyright (c) 2018 Olle Eriksson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
----------------------------------------------------------------------------*/

#include <SDL_ttf.h>

#include "Typewriter.h"

Typewriter::Typewriter() {}

Typewriter::Typewriter(std::string n_font_name, int n_font_size) {
  font_name = n_font_name;
  font_size = n_font_size;
  leading = (font_size * 4) / 3;
  generateFontAtlas();
}

char* Typewriter::latin9_To_UTF8(unsigned char latin9_c) {
  /* Converts character from Latin-9 to UTF-8 and returns result as a null
     terminated string. */
  char* utf8_str;
  if(32 <= latin9_c && latin9_c <= 126) {
    utf8_str = new char[2];
    utf8_str[0] = latin9_c;
    utf8_str[1] = '\0';
  }
  else if(160 <= latin9_c && latin9_c <= 255) {
    utf8_str = new char[3];
    utf8_str[0] = latin9_c < 192 ? '\xc2' : '\xc3';
    utf8_str[1] = latin9_c < 192 ? latin9_c : latin9_c - 64;
    utf8_str[2] = '\0';
  }
  else {
    utf8_str = new char[1];
    utf8_str[0] = '\0';
  }
  return utf8_str;
}

void Typewriter::generateFontAtlas() {
  TTF_Font *font = TTF_OpenFont(font_name.c_str(), font_size);
  for(int n = 32; n < 256; n++) { /* We skip control characters etc. */
    if(n == 127)
      n = 160;
    SDL_Surface *character;
    char* utf8_str = latin9_To_UTF8(n);
    character = TTF_RenderUTF8_Solid(font, utf8_str, color);
    delete[] utf8_str;
    Img i;
    i.loadSurface(character);
    SDL_FreeSurface(character);
    font_atlas.push_back(i);
  }
  TTF_CloseFont(font);
}

Img* Typewriter::getCharacter(char c) {
  if(32 <= c && c <= 126)
    return &font_atlas[int(c) - 32];
  if(-96 <= c && c <= -1)
    return &font_atlas[int(c) + 191];
  return nullptr;
}

int Typewriter::getFontSize() const {
  return font_size;
}

int Typewriter::getFontHeight() const {
  return font_atlas[0].getHeight();
}

int Typewriter::getLeading() const {
  return leading;
}

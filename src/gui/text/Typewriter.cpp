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

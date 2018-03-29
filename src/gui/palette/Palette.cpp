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

#include "Palette.h"

Palette::Palette() {
  beacon_number = -1;
  city_beacon_symbol = 1;
  setDefaultPalette();
}

void Palette::setCitySymbols(unsigned int s) {
  city_def_symbol = Img(s, s, 0xFF000000);
  for(unsigned int x = 0; x < s; x++) { for(unsigned int y = 0; y < s; y++) {
      if((x == 1 || x == s - 2 || y == 1 || y == s - 2) &&
         (x != 0 && x != s - 1 && y != 0 && y != s - 1)    )
        city_def_symbol.setPixel(x, y, city_def_color);
  } }
  city_active_symbol = Img(s, s, 0xFF000000);
  for(unsigned int x = 0; x < s; x++) { for(unsigned int y = 0; y < s; y++) {
      if((x == 1 || x == s - 2 || y == 1 || y == s - 2) &&
         (x != 0 && x != s - 1 && y != 0 && y != s - 1)    )
        city_active_symbol.setPixel(x, y, city_active_color);
  } }
  city_selected_symbol = Img(s, s, 0xFF000000);
  for(unsigned int x = 0; x < s; x++) { for(unsigned int y = 0; y < s; y++) {
      if((x == 1 || x == s-2 || y == 1 || y == s-2) &&
         (x != 0 && x != s-1 && y != 0 && y != s - 1)  )
        city_selected_symbol.setPixel(x, y, city_selected_color);
  } }
  city_beacon_symbol_i = Img(s, s, city_beacon_i_color);
  city_beacon_symbol_ii = Img(s, s, 0xFF000000);
  for(unsigned int x = 0; x < s; x++) { for(unsigned int y = 0; y < s; y++) {
      if((x == 1 || x == s - 2 || y == 1 || y == s - 2) &&
        (x != 0 && x != s - 1 && y != 0 && y != s - 1)    )
        city_beacon_symbol_ii.setPixel(x, y, city_beacon_ii_color);
  } }
}

Img* Palette::getCitySymbol(int city_number, unsigned int flags) {
  bool beacon_this = false;
  for(int i = 0; i < (int) city_beacon_numbers.size(); i++) {
    if(city_beacon_numbers.at(i) == city_number) { beacon_this = true; break;}
  }
  if(beacon_this) {
    if(cityBeaconOn()) {
      if(city_beacon_symbol == 1) { return &city_beacon_symbol_i; }
      else { return &city_beacon_symbol_ii; }
    }
  }
  else if(flags & CITY_IS_PLAIN || city_flag_override & CITY_IS_PLAIN)
                                                         { return 0;                    }
  else if(flags & CITY_IS_SELECTED & city_flag_override) { return &city_selected_symbol; }
  else if(flags & CITY_IS_ACTIVE & city_flag_override)   { return &city_active_symbol;   }
  return &city_def_symbol;
}

void Palette::step() {
  if(beacon_timer.isExpired()     ) { beacon_color = def_beacon_color; }
  if(city_beacon_timer.isExpired()) { city_beacon_numbers.clear();     }
}

void Palette::setBeacon(int region_number, double time, Uint32 color) {
  beacon_number = region_number;
  beacon_timer.setTimer(time);
  beacon_color = color;
}

void Palette::setBeacon(int region_number, double time) {
  setBeacon(region_number, time, def_beacon_color);
}

bool Palette::beaconOn() const {
  if(beacon_timer.isExpired() == false
     && (beacon_timer.getElapsedMilliseconds() / 80) % 2 == 0)
    return true;
  return false;
}

void Palette::setCityBeacon(std::vector<int> city_numbers, double time, int symbol) {
  if(city_beacon_numbers.size() > 0) { city_beacon_numbers.clear(); }
  city_beacon_numbers = city_numbers;
  city_beacon_timer.setTimer(time);
  city_beacon_symbol = symbol;
}

bool Palette::cityBeaconOn() const {
  if(city_beacon_timer.isExpired() == false
     && (city_beacon_timer.getElapsedMilliseconds() / 80) % 2 == 0)
    return true;
  return false;
}

void Palette::clearAllBeacons() {
  beacon_timer.setTimer(0.0);
  beacon_number = -1;
  beacon_color = def_beacon_color;
  city_beacon_timer.setTimer(0.0);
  city_beacon_numbers.clear();
  city_beacon_symbol = 1;
}

void Palette::setPaletteSize(int new_size) {
  palette_size = new_size;
  main_palette.resize(palette_size);
}

void Palette::setDefaultPalette() {
  id = 0;
  setPaletteSize(11);
  active_color     = 0xFFFFCC33; border_color     = 0xFF000000; clicked_color    = 0xFFFF0000;
  def_beacon_color = 0xFF0000FF; def_land_color   = 0xFF993300; unknown_color    = 0xFF999999;
  water_color      = 0xFF006666; main_palette[0]  = 0xFF993333; main_palette[1]  = 0xFF996633;
  main_palette[2]  = 0xFF999933; main_palette[3]  = 0xFF669933; main_palette[4]  = 0xFF339933;
  main_palette[5]  = 0xFF339966; main_palette[6]  = 0xFF339999; main_palette[7]  = 0xFF336699;
  main_palette[8]  = 0xFF663399; main_palette[9]  = 0xFF993399; main_palette[10] = 0xFF993366;
  flag_override = IS_ACTIVE | IS_BORDER | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFFFFFFF; city_selected_color = 0xFF33FF66;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFFFF0000;
  setCitySymbols(7);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 0;
}

void Palette::setOllePalette() {
  id = 1;
  setPaletteSize(1);
  active_color     = 0xFFCC3333; border_color    = 0xFF000000; clicked_color = 0xFFCC3333;
  def_beacon_color = 0xFF0000FF; def_land_color  = 0xFF993300; unknown_color = 0xFFCC3333;
  water_color      = 0xFF006666; main_palette[0] = 0xFFCC3333;
  flag_override = IS_ACTIVE | IS_BORDER | IS_PLAIN | IS_SELECTED;
  city_def_color = 0xFF00FF00; city_active_color = 0xFF00FF00; city_selected_color = 0xFF00FF00;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF00FF00;
  setCitySymbols(7);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED | CITY_IS_PLAIN;
  border_mode = 3;
}

void Palette::setColorBrewerQ61Palette() {
  id = 2;
  setPaletteSize(5);
  active_color     = 0xFFCCCCCC; border_color    = 0xFF000000; clicked_color   = 0xFFEEEEEE;
  def_beacon_color = 0xFF000000; def_land_color  = 0xFF7FC97F; unknown_color   = 0xFF333333;
  water_color      = 0xFFFFFFFF; main_palette[0] = 0xFFBEAED4; main_palette[1] = 0xFFFDC086;
  main_palette[2]  = 0xFFFFFF99; main_palette[3] = 0xFF386CB0; main_palette[4] = 0xFFF0027F;
  flag_override = IS_ACTIVE | IS_BORDER | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFCCCCCC; city_selected_color = 0xFFFFFFFF;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF666666;
  setCitySymbols(9);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 0;
}

void Palette::setColorBrewerQ62Palette() {
  id = 3;
  setPaletteSize(5);
  active_color     = 0xFFCCCCCC; border_color    = 0xFF000000; clicked_color   = 0xFFEEEEEE;
  def_beacon_color = 0xFF000000; def_land_color  = 0xFFfBB4AE; unknown_color   = 0xFF333333;
  water_color      = 0xFFFFFFFF; main_palette[0] = 0xFFB3CDE3; main_palette[1] = 0xFFCCEBC5;
  main_palette[2]  = 0xFFDECBE4; main_palette[3] = 0xFFFED9A6; main_palette[4] = 0xFFFFFFCC;
  flag_override = IS_ACTIVE | IS_BORDER | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFCCCCCC; city_selected_color = 0xFFFFFFFF;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF666666;
  setCitySymbols(9);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 0;
}

void Palette::setColorBrewerQ121Palette() {
  id = 4;
  setPaletteSize(11);
  active_color     = 0xFFCCCCCC; border_color    = 0xFF000000; clicked_color    = 0xFFEEEEEE;
  def_beacon_color = 0xFF000000; def_land_color  = 0xFF8DD3C7; unknown_color    = 0xFF333333;
  water_color      = 0xFFFFFFFF; main_palette[0] = 0xFFFFFFB3; main_palette[1]  = 0xFFBEBADA;
  main_palette[2]  = 0xFFFB8072; main_palette[3] = 0xFF80B1D3; main_palette[4]  = 0xFFFDB462;
  main_palette[5]  = 0xFFB3DE69; main_palette[6] = 0xFFFCCDE5; main_palette[7]  = 0xFFD9D9D9;
  main_palette[8]  = 0xFFBC80BD; main_palette[9] = 0xFFCCEBC5; main_palette[10] = 0xFFFFED6F;
  flag_override = IS_ACTIVE | IS_BORDER | IS_PLAIN | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFCCCCCC; city_selected_color = 0xFFFFFFFF;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF666666;
  setCitySymbols(9);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 0;
}

void Palette::setColorBrewerQ122Palette() {
  id = 5;
  setPaletteSize(11);
  active_color     = 0xFFCCCCCC; border_color    = 0xFF000000; clicked_color    = 0xFFEEEEEE;
  def_beacon_color = 0xFF000000; def_land_color  = 0xFFA6CEE3; unknown_color    = 0xFF333333;
  water_color      = 0xFFFFFFFF; main_palette[0] = 0xFF1F78B4; main_palette[1]  = 0xFFB2DF8A;
  main_palette[2]  = 0xFF33A02C; main_palette[3] = 0xFFFB9A99; main_palette[4]  = 0xFFE31A1C;
  main_palette[5]  = 0xFFFDBF6F; main_palette[6] = 0xFFFF7F00; main_palette[7]  = 0xFFCAB2D6;
  main_palette[8]  = 0xFF6A3D9A; main_palette[9] = 0xFFFFFF99; main_palette[10] = 0xFFB15928;
  flag_override = IS_ACTIVE | IS_BORDER | IS_PLAIN | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFCCCCCC; city_selected_color = 0xFFFFFFFF;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF666666;
  setCitySymbols(9);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 0;
}

void Palette::setDarkGrayPalette() {
  id = 6;
  setPaletteSize(5);
  active_color     = 0xFFCCCCCC; border_color    = 0xFF000000; clicked_color   = 0xFFEEEEEE;
  def_beacon_color = 0xFF000000; def_land_color  = 0xFF333333; unknown_color   = 0xFF333333;
  water_color      = 0xFF000000; main_palette[0] = 0xFF444444; main_palette[1] = 0xFF555555;
  main_palette[2]  = 0xFF666666; main_palette[3] = 0xFF777777; main_palette[4] = 0xFF888888;
  flag_override = IS_ACTIVE | IS_BORDER | IS_SELECTED;
  city_def_color = 0xFF999999; city_active_color = 0xFFCCCCCC; city_selected_color = 0xFFFFFFFF;
  city_beacon_i_color = 0xFF00FF00; city_beacon_ii_color = 0xFF666666;
  setCitySymbols(9);
  city_flag_override = CITY_IS_ACTIVE | CITY_IS_SELECTED;
  border_mode = 6;
}

void Palette::setPalette(int n) {
  static void (Palette::*palette_ps[])(void)
    = {setDefaultPalette,
       setOllePalette,
       setColorBrewerQ61Palette,
       setColorBrewerQ62Palette,
       setColorBrewerQ121Palette,
       setColorBrewerQ122Palette,
       setDarkGrayPalette};
  if(0 <= n && n < sizeof(palette_ps) / sizeof(*palette_ps))
    (*this.*palette_ps[n])();
}

int Palette::getId() {
  return id;
}

vector<std::string> Palette::getPaletteNames() {
  static std::vector<std::string> palette_names
    = {"Default",
       "Olle Palette",
       "ColorBrewer Q6 1",
       "ColorBrewer Q6 2",
       "ColorBrewer Q12 1",
       "ColorBrewer Q12 2",
       "Dark Gray Palette"};
  return palette_names;
}

Uint32 Palette::getColor(int region_number, int x, int y, unsigned int flags) const {
  Uint32 color;
  if      (flags & IS_BORDER & flag_override)   { return border_color;   }
  else if (region_number == beacon_number && beaconOn()) {
    color = beacon_color;
  }
  else if (flags & IS_SELECTED & flag_override) { color = clicked_color; }
  else if (flags & IS_ACTIVE & flag_override)   { color = active_color;  }
  else if (region_number == -1)                 { return water_color;    }
  else if (region_number == -2)                 { return def_land_color; }
  else if (region_number <= -3)                 { return unknown_color;  }
  else { color = main_palette[region_number % palette_size]; }
  if(flags & IS_PLAIN || flag_override & IS_PLAIN) {
    return color;
  }
  int pattern = region_number % 7;
  if      (pattern == 0 && (x - y) % 3 == 0)   return getAltColor(color);
  else if (pattern == 1 && (x + y) % 3 == 0)   return getAltColor(color);
  else if (pattern == 2 && (x * y) % 3 == 1)   return getAltColor(color);
  else if (pattern == 3 && (x * y) % 3 == 2)   return getAltColor(color);
  else if (pattern == 4 && y % 3 - x % 2 == 0) return getAltColor(color);
  else if (pattern == 5 && x % 3 - y % 2 == 0) return getAltColor(color);
  else if (pattern == 6 && y % 2 == 0 &&
                             (y + x) % 4 == 0) return getAltColor(color);
  return color;
}

Uint32 Palette::getAltColor(Uint32 color) const {
  Uint32 v = 0x20;
  Uint32 r = (color & 0x00FF0000) >> 16;
  Uint32 g = (color & 0x0000FF00) >> 8;
  Uint32 b = (color & 0x000000FF);
  r = r < v ? 0 : r - v;
  g = g < v ? 0 : g - v;
  b = b < v ? 0 : b - v;
  return (r << 16) + (g << 8) + b;
}

Uint32 Palette::getColor(int n, int x, int y) const {
  return getColor(n, x, y, 0x000);
}

int Palette::getBorderMode() const {
  return border_mode;
}

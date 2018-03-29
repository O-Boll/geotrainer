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

#ifndef PALETTE_H
#define PALETTE_H

#include <vector>
#include <string>

#include "../../timer/Timer.h"
#include "../img/Img.h"

#include <SDL.h>

class Palette {

  private:

    int id;

    Uint32 active_color,
           border_color,
           clicked_color,
           def_beacon_color,
           def_land_color,
           unknown_color,
           water_color;

    std::vector<Uint32> main_palette;

    unsigned int palette_size,
                 flag_override,
                 city_flag_override;

    int border_mode;

    Timer beacon_timer;
    int beacon_number;
    Timer city_beacon_timer;
    int city_beacon_symbol;

    Uint32 beacon_color;

    std::vector<int> city_beacon_numbers;

    Uint32 city_def_color,
           city_active_color,
           city_selected_color,
           city_beacon_i_color,
           city_beacon_ii_color;

    Img city_def_symbol,
        city_active_symbol,
        city_selected_symbol,
        city_beacon_symbol_i,
        city_beacon_symbol_ii;

    void setPaletteSize(int new_size);

  public:

    static const unsigned int IS_BORDER   = 0x01,
                              IS_SELECTED = 0x02,
                              IS_ACTIVE   = 0x04,
                              IS_PLAIN    = 0x08;

    static const unsigned int CITY_IS_SELECTED = 0x01,
                              CITY_IS_ACTIVE   = 0x02,
                              CITY_IS_PLAIN    = 0x04;


    Palette();

    void setCitySymbols(unsigned int s);

    Img* getCitySymbol(int city_number, unsigned int flags);

    void step();

    void setBeacon(int region_number, double time, Uint32 color);

    void setBeacon(int region_number, double time);

    void setCityBeacon(std::vector<int> city_numbers, double time, int symbol);

    bool beaconOn() const;

    bool cityBeaconOn() const;

    void clearAllBeacons();

    Uint32 getColor(int n, int x, int y, unsigned int flags) const;

    Uint32 getColor(int n, int x, int y) const;

    Uint32 getAltColor(Uint32 color) const;

    int getBorderMode() const;

    void setPalette(int n);

    int getId();

    std::vector<std::string> getPaletteNames();

    void setDefaultPalette();
    void setOllePalette();
    void setColorBrewerQ61Palette();
    void setColorBrewerQ62Palette();
    void setColorBrewerQ121Palette();
    void setColorBrewerQ122Palette();
    void setDarkGrayPalette();

};

#endif


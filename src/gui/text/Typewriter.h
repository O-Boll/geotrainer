#ifndef TYPEWRITER_H
#define TYPEWRITER_H

#include <string>
#include <vector>

#include "../img/Img.h"

class Typewriter {

  private:

    std::string font_name;

    int font_size;

    int leading;

    SDL_Color color;

    std::vector<Img> font_atlas;

    void generateFontAtlas();

    static char* latin9_To_UTF8(unsigned char latin9_c);

  public:

    Typewriter();

    Typewriter(std::string font_name, int font_size);

    Img *getCharacter(char c);

    int getFontSize() const;

    int getFontHeight() const;

    int getLeading() const;

};

#endif

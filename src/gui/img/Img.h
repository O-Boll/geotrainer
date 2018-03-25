#ifndef IMG_H
#define IMG_H

#include <vector>

#include <SDL.h>

class Img {

  private:

    int w, h;

    Uint32 *pixels;

    bool isDifferent(Uint32 A, Uint32 B, int mode) const;

  public:

    Img();

    Img(const Img& img);

    Img(int w, int h, Uint32 color);

    ~Img();

    Img& operator=(const Img& img);

    void loadBMP(const char* f_name);

    void loadRegionBMP(const char* f_name,
                       std::vector<int>& region_center_x,
                       std::vector<int>& region_center_y);

    void loadBMPtoSizeKeepAspect(const char *f_name, int n_w, int n_h);

    void loadSurface(SDL_Surface *surf);

    bool isLoaded() const;

    void fillImg(Uint32 color);

    bool isBorder(int x, int y, int mode) const;

    Uint32* getPixels() const;

    Uint32 getPixelAt(int x, int y) const;

    int getWidth() const;

    int getHeight() const;

    void setPixel(int x, int y, Uint32 color);

};

#endif

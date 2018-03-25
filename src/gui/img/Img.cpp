#include "Img.h"

Img::Img() {
  w = h = 0;
  pixels = nullptr;
}

Img::Img(const Img& img) {
  w = img.w;
  h = img.h;
  pixels = new Uint32[w * h];
  for(int i = 0; i < w * h; i++)
    pixels[i] = img.pixels[i];
}

Img::Img(int n_w, int n_h, Uint32 color) {
  w = n_w;
  h = n_h;
  if(n_w > 0 && n_h > 0) {
    pixels = new Uint32[n_w * n_h];
    for(int i = 0; i < n_w * n_h; i++)
      pixels[i] = color;
  }
  else
    pixels = nullptr;
}

Img::~Img() {
  delete[] pixels;
}

Img& Img::operator=(const Img& img) {
  w = img.w;
  h = img.h;
  delete[] pixels;
  pixels = new Uint32[w * h];
  for(int i = 0; i < w * h; i++)
    pixels[i] = img.pixels[i];
  return *this;
}

void Img::loadBMP(const char *f_name) {
  SDL_Surface *surf = SDL_LoadBMP(f_name);
  if(surf == 0) return; /* XXX */
  w = surf->w;
  h = surf->h;
  delete[] pixels;
  pixels = new Uint32[w * h];
  Uint32 *n_pixels = (Uint32*) surf->pixels;
  for(int i = 0; i < w * h; i++) {
    pixels[i] = n_pixels[i];
  }
  SDL_FreeSurface(surf);
}

void Img::loadRegionBMP(const char* f_name,
                        std::vector<int>& region_center_x,
                        std::vector<int>& region_center_y) {
  loadBMP(f_name);
  int regions, size;
  regions = 0;
  size = w * h;
  for(int i = 0; i < size; i++) {
    int r_num = (pixels[i] & 0xFF); /* region number */
    if (r_num >= regions) { regions = r_num + 1; }
  }
  region_center_x.resize(regions);
  fill(region_center_x.begin(), region_center_x.end(), 0);
  region_center_y.resize(regions);
  fill(region_center_y.begin(), region_center_y.end(), 0);
  std::vector<int> pixel_numbers(regions, 0);

  for(int i = 0; i < size; i++) {
    int r_num = (pixels[i] & 0x00FFFFFF);
    if (r_num < regions) {
      int x, y;
      x = i % w;
      y = i / w;
      region_center_x[r_num] += x;
      region_center_y[r_num] += y;
      pixel_numbers  [r_num] += 1;
    }
  }
  for(int i = 0; i < regions; i++) {
    if(pixel_numbers[i] != 0) {
      region_center_x[i] /= pixel_numbers[i];
      region_center_y[i] /= pixel_numbers[i];
    }
  }
}

void Img::loadBMPtoSizeKeepAspect(const char *f_name, int n_w, int n_h) {
  SDL_Surface *surf = SDL_LoadBMP(f_name);
  w = n_w;
  h = n_h;
  delete[] pixels;
  pixels = new Uint32[w * h];
  int row_max, col_max, row_start, col_start;
  if(surf->w * h <= surf->h * w) {
    row_max = h;
    col_max = h * surf->w / surf->h;
    row_start = 0;
    col_start = (w - col_max) / 2;
  }
  else {
    row_max = w * surf->h / surf->w;
    col_max = w;
    row_start = (h - row_max) / 2;
    col_start = 0;
  }
  Uint32 *n_pixels = (Uint32*) surf->pixels;
  int i_row, i_col, row, col;
  for(int i = 0; i < w * h; i++) {
    i_row = i / w;
    i_col = i % w;
    if(row_start <= i_row && i_row < row_max + row_start &&
       col_start <= i_col && i_col < col_max + col_start    ) {
      row = (i_row - row_start) * surf->h / row_max;
      col = (i_col - col_start) * surf->w / col_max;
      pixels[i] = n_pixels[row * surf->w + col];
    }
    else {
      pixels[i] = 0xFF000000;
    }
  }
  SDL_FreeSurface(surf);
}

void Img::loadSurface(SDL_Surface *surf) {
  w = surf->w;
  h = surf->h;
  delete[] pixels;
  pixels = new Uint32[w * h];
  Uint32 *t = pixels;
  Uint8 *o = (Uint8*) (surf->pixels);
  int n = 0;
  for(int i = 0; i < h; i++) {
    for(int j = 0; j < w; j++) {
      if(*o) *t = 0xFFFFFFFF;
      else *t = 0xFF00FF00;
      n++;
      o++;
      t++;
    }
    while(n % 4 != 0) { n++; o++; }
  }
}

bool Img::isLoaded() const {
  return pixels != nullptr;
}

void Img::fillImg(Uint32 color) {
  for(int n = 0; n < w * h; n++)
    pixels[n] = color;
}

bool Img::isBorder(int x, int y, int mode) const {
  if(x >= 0 && x < w && y >= 0 && y < h) {
    Uint32 color = pixels[y * w + x];
    if(x > 0 && y > 0) {
      if(isDifferent(color, pixels[(y - 1) * w + (x - 1)], mode)) { return true; }
      if(isDifferent(color, pixels[(y - 1) * w + (x + 0)], mode)) { return true; }
      if(isDifferent(color, pixels[(y + 0) * w + (x - 1)], mode)) { return true; }
    }
    else if(x + 1 < w && y + 1 < h) {
      if(isDifferent(color, pixels[(y + 1) * w + (x + 1)], mode)) { return true; }
      if(isDifferent(color, pixels[(y + 1) * w + (x + 0)], mode)) { return true; }
      if(isDifferent(color, pixels[(y + 0) * w + (x + 1)], mode)) { return true; }
    }
    else if(x > 1 && y + 1 < h) {
      if(isDifferent(color, pixels[(y + 1) * w + (x - 1)], mode)) { return true; }
    }
    else if(x + 1 < w && y > 1) {
      if(isDifferent(color, pixels[(y - 1) * w + (x + 1)], mode)) { return true; }
    }
  }
  return false;
}

bool Img::isDifferent(Uint32 A, Uint32 B, int mode) const {
  /* mode = 0 looks for all differences
     mode = 1 looks for differences between active and inative areas
     mode = 2 looks for differences between land and sea
     mode = 3 combines mode 2 and 3
     mode = 4 looks for differences between active areas
     mode = 5 looks for differences between active areas and inactive land areas
     mode = 6 combines mode 4 and 5
  */
  if (mode == 0) {
    if (A != B) { return true; }
    return false;
  }
  if (mode == 1 || mode == 3) {
    if((A == 0xFF00FF00 || A == 0xFF009900) && (B != 0xFF00ff00 && B != 0xFF009900)) { return true; }
    if((B == 0xFF00FF00 || B == 0xFF009900) && (A != 0xFF00FF00 && A != 0xFF009900)) { return true; }
    if (mode != 3) { return false; }
  }
  if (mode == 2 || mode == 3) {
    if((A == 0xFF00FF00 && B != A) || (B == 0xFF00FF00 && B != A)) { return true; }
  }
  if (mode == 4 || mode == 6) {
    if((A != 0xFF00FF00 && A != 0xFF009900) && (B != 0xFF00FF00 && B != 0xFF009900) && A != B) { return true; }
  }
  if (mode == 5 || mode == 6) {
    if(A != 0xFF00FF00 && B != 0xFF00FF00) {
      if((A == 0xFF009900 && A != B) || (B == 0xFF009900 && A != B)) { return true; }
    }
  }
  return false;
}

Uint32* Img::getPixels() const {
  return pixels;
}

Uint32 Img::getPixelAt(int x, int y) const {
  return pixels[y * w + x];
}

int Img::getWidth() const {
  return w;
}

int Img::getHeight() const {
  return h;
}

void Img::setPixel(int x, int y, Uint32 color) {
  pixels[y * w + x] = color;
}

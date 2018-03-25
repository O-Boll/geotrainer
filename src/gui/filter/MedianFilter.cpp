#include "MedianFilter.h"

using std::uint8_t;
using std::uint32_t;

MedianFilter::MedianFilter() {
  s_screen = 0;
  s_width = s_height = scale = 0;
}

MedianFilter::MedianFilter(uint32_t* screen, uint32_t width, uint32_t height)
  : Filter(screen, width, height) {

  s_screen = 0;
  s_width = s_height = scale = 0;
}

MedianFilter::~MedianFilter() { }

void MedianFilter::setSmallScreen(uint32_t* n_s_screen,
                                  uint32_t n_s_width,
                                  uint32_t n_s_height,
                                  uint32_t n_scale) {
  s_screen = n_s_screen;
  s_width = n_s_width;
  s_height = n_s_height;
  scale = n_scale;
}

void MedianFilter::apply_() {
  uint32_t x, y, color, i;
  for(y = 0; y < s_height; y++) {
    for(x = 0; x < s_width; x++) {
      color = s_screen[y * s_width + x];
      i = (scale * y) * width + (scale * x);
      if(calculateMedians(x, y)) {
        screen[i] = r.ul;
        screen[i + scale - 1] = r.ur;
        screen[i + (scale - 1) * width] = r.ll;
        screen[i + (scale - 1) * width + (scale - 1)] = r.lr;
      }
    }
  }
}

uint32_t MedianFilter::getBrightness(uint32_t color) {
  /* return r + g + b */
  return ((color >> 16) & 0xFF) + ((color >> 8) & 0xFF) + (color & 0xFF);
}

/* returns false if medians are the same as already drawn */
bool MedianFilter::calculateMedians(uint32_t x, uint32_t y) {

  uint32_t ul,  uc,  ur,  ml,  mc,  mr,  ll,  lc,  lr,
           ulb, ucb, urb, mlb, mcb, mrb, llb, lcb, lrb,
           i;

  i = y * s_width + x;
  mc = s_screen[i];

  uc = (                    y == 0           ) ? mc : s_screen[i - s_width    ];
  ml = (x == 0                               ) ? mc : s_screen[i           - 1];
  mr = (x == s_width - 1                     ) ? mc : s_screen[i           + 1];
  lc = (                    y == s_height - 1) ? mc : s_screen[i + s_width    ];

  if(mc == uc) if(mc == ml) if(mc == mr) if(mc == lc) return false;

  ul = (x == 0           || y == 0           ) ? mc : s_screen[i - s_width - 1];
  ur = (x == s_width - 1 || y == 0           ) ? mc : s_screen[i - s_width + 1];
  ll = (x == 0           || y == s_height - 1) ? mc : s_screen[i + s_width - 1];
  lr = (x == s_width - 1 || y == s_height - 1) ? mc : s_screen[i + s_width + 1];

  ulb = getBrightness(ul);
  ucb = getBrightness(uc);
  urb = getBrightness(ur);
  mlb = getBrightness(ml);
  mcb = getBrightness(mc);
  mrb = getBrightness(mr);
  llb = getBrightness(ll);
  lcb = getBrightness(lc);
  lrb = getBrightness(lr);

  /* upper left */
  if(mcb <= mlb) {
    if(mcb <= ulb) {
      if(mcb <= ucb) {
        if(mlb <= ulb) {
          if(mlb <= ucb) r.ul = ml;
          else r.ul = uc;
        }
        else {
          if(ulb <= ucb) r.ul = ul;
          else r.ul = uc;
        }
      }
      else r.ul = mc;
    }
    else r.ul = mc;
  }
  else if(mcb <= ulb) r.ul = mc;
  else if(mcb <= ucb) r.ul = mc;
  else {
    if(mlb > ulb) {
      if(mlb > ucb) r.ul = ml;
      else r.ul = uc;
    }
    else {
      if(ulb > ucb) r.ul = ul;
      else r.ul = uc;
    }
  }

  /* upper right */
  if(mcb <= ucb) {
    if(mcb <= urb) {
      if(mcb <= mrb) {
        if(ucb <= urb) {
          if(ucb <= mrb) r.ur = uc;
          else r.ur = mr;
        }
        else {
          if(urb <= mrb) r.ur = ur;
          else r.ur = mr;
        }
      }
      else r.ur = mc;
    }
    else r.ur = mc;
  }
  else if(mcb <= urb) r.ur = mc;
  else if(mcb <= mrb) r.ur = mc;
  else {
    if(ucb > urb) {
      if(ucb > mrb) r.ur = uc;
      else r.ur = mr;
    }
    else {
      if(urb > mrb) r.ur = ur;
      else r.ur = mr;
    }
  }

  /* lower right */
  if(mcb <= mrb) {
    if(mcb <= lrb) {
      if(mcb <= lcb) {
        if(mrb <= lrb) {
          if(mrb <= lcb) r.lr = mr;
          else r.lr = lc;
        }
        else {
          if(lrb <= lcb) r.lr = lr;
          else r.lr = lc;
        }
      }
      else r.lr = mc;
    }
    else r.lr = mc;
  }
  else if(mcb <= lrb) r.lr = mc;
  else if(mcb <= lcb) r.lr = mc;
  else {
    if(mrb > lrb) {
      if(mrb > lcb) r.lr = mr;
      else r.lr = lc;
    }
    else {
      if(lrb > lcb) r.lr = lr;
      else r.lr = lc;
    }
  }

  /* lower left */
  if(mcb <= lcb) {
    if(mcb <= llb) {
      if(mcb <= mlb) {
        if(lcb <= llb) {
          if(lcb <= mlb) r.ll = lc;
          else r.ll = ml;
        }
        else {
          if(llb <= mlb) r.ll = ll;
          else r.ll = ml;
        }
      }
      else r.ll = mc;
    }
    else r.ll = mc;
  }
  else if(mcb <= llb) r.ll = mc;
  else if(mcb <= mlb) r.ll = mc;
  else {
    if(lcb > llb) {
      if(lcb > mlb) r.ll = lc;
      else r.ll = ml;
    }
    else {
      if(llb > mlb) r.ll = ll;
      else r.ll = ml;
    }
  }

  return true;
}

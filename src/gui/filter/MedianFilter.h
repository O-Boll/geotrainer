#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <cstdint>

#include "Filter.h"

using std::uint32_t;

class MedianFilter : public Filter {

  private:

    struct median_return {
      std::uint32_t ul, ur, ll, lr;
    };

    median_return r;

    std::uint32_t* s_screen;
    std::uint32_t s_width, s_height, scale;

    virtual void apply_();

  public:

    MedianFilter();
    MedianFilter(std::uint32_t* screen, std::uint32_t width, std::uint32_t height);
    void setSmallScreen(std::uint32_t* n_s_screen,
                        std::uint32_t n_s_width,
                        std::uint32_t n_s_height,
                        std::uint32_t n_scale);
    virtual ~MedianFilter();
    std::uint32_t getBrightness(std::uint32_t color);
    bool calculateMedians(std::uint32_t x, std::uint32_t y);

};

#endif

#ifndef CANVAS_FILTER_H
#define CANVAS_FILTER_H

#include <cstdint>

#include "Filter.h"

class CanvasFilter : public Filter {

  private:

    std::uint8_t* canvas;
    std::uint32_t canvas_width, canvas_height;
    int offset_x, offset_y;

    virtual void apply_();

  public:

    CanvasFilter();
    CanvasFilter(std::uint32_t* screen, std::uint32_t width, std::uint32_t height);
    CanvasFilter(const CanvasFilter& cf);
    virtual CanvasFilter& operator=(const CanvasFilter& cf);
    virtual ~CanvasFilter();
    void loadCanvas(const char* filename);
    void setOffset(int n_offset_x, int n_offset_y);

};

#endif

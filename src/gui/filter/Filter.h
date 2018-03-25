#ifndef FILTER_H
#define FILTER_H

#include <cstdint>

class Filter {

  private:

    bool active;

    virtual void apply_() = 0;

  protected:

    uint32_t* screen;
    uint32_t width, height;

  public:

    Filter();
    Filter(uint32_t* screen, uint32_t width, uint32_t height);
    virtual ~Filter();
    void apply();
    bool isActive() const;
    void activate();
    void deactivate();
};

#endif

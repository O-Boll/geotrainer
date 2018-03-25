#include "Filter.h"

Filter::Filter() : active(false), screen(nullptr) {}

Filter::Filter(uint32_t* screen, uint32_t width, uint32_t height)
  : screen(screen), width(width), height(height), active(false) { }

Filter::~Filter() {}

void Filter::apply() {
  if(active)
    apply_();
}

bool Filter::isActive() const {
  return active;
}

void Filter::activate() {
  active = true;
}

void Filter::deactivate() {
  active = false;
}

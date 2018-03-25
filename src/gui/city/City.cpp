#include "City.h"

City::City() {
  x = y = 0;
}

City::City(int n_x, int n_y, std::string n_name) {
  name = n_name;
  x = n_x;
  y = n_y;
}

void City::setName(std::string n_name) {
  name = n_name;
}

std::string City::getName() const {
  return name;
}

void City::setCoordinates(int n_x, int n_y) {
  x = n_x;
  y = n_y;
}

int City::getXCoordinate() const {
  return x;
}

int City::getYCoordinate() const {
  return y;
}

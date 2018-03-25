#ifndef CITY_H
#define CITY_H

#include <string>

using namespace std;

class City {

  private:

    std::string name;

    int x, y;

  public:

    City();

    City(int n_x, int n_y, std::string n_name);

    void setName(std::string name);

    std::string getName() const;

    void setCoordinates(int n_x, int n_y);

    int getXCoordinate() const;

    int getYCoordinate() const;

};

#endif

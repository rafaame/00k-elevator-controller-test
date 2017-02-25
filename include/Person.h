#ifndef __PERSON_CONTROLLER_H__
#define __PERSON_CONTROLLER_H__

#include "common.h"

class Floor;

using namespace std;

class Person {
private:
    Floor *destinationFloor;

public:
    Person();
    ~Person();

    Floor *getDestinationFloor() { return destinationFloor; }
    void setDestinationFloor(Floor *destinationFloor) { this->destinationFloor = destinationFloor; }
};

#endif

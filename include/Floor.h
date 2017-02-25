#ifndef __FLOOR_CONTROLLER_H__
#define __FLOOR_CONTROLLER_H__

#include "common.h"

class Person;

using namespace std;

class Floor {
private:
    uint8_t number;

    PeopleVector waitingPeople;

public:
    Floor(uint8_t number, uint8_t numberPeople);
    ~Floor();

    uint8_t getNumber() { return number; }
    uint8_t getNumberWaitingPeople() { return waitingPeople.size(); }
    PeopleVector &getWaitingPeople() { return waitingPeople; }
};

#endif

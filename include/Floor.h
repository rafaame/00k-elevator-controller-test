#ifndef __FLOOR_CONTROLLER_H__
#define __FLOOR_CONTROLLER_H__

#include "common.h"

class Person;

using namespace std;

class Floor {
private:
    uint8_t number;

    PeopleVector waitingPeople;
    PeopleVector deliveredPeople;

public:
    Floor(uint8_t number);
    ~Floor();

    uint8_t getNumber() { return number; }
    uint8_t getNumberWaitingPeople() { return waitingPeople.size(); }
    PeopleVector &getWaitingPeople() { return waitingPeople; }

    void deliverPerson(Person *person);

    void init(uint8_t numberPeople);
    void clear();
};

#endif

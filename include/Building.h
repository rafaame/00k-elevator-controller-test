#ifndef __BUILDING_H__
#define __BUILDING_H__

#include "common.h"

class Elevator;

using namespace std;

class Building {
private:
    uint8_t numberWaitingPeople;

    FloorMap floors;
    Elevator *elevator;

public:
    Building();
    ~Building();

    Elevator *getElevator() { return elevator; }

    void init();
    void run();
};

#endif

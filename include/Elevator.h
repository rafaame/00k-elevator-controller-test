#ifndef __ELEVATOR_H__
#define __ELEVATOR_H__

#include "common.h"

class Floor;

using namespace std;

class Elevator {
private:
    Floor *currentFloor;
    Floor *nextFloor;
    ElevatorDirection_t direction;

    FloorMap *floors;
    PeopleVector people;

    uint8_t numberDeliveredPeople;

public:
    Elevator(FloorMap *floors);
    ~Elevator();

    Floor *getCurrentFloor() { return currentFloor; }
    uint8_t getNumberFloors() { return floors->size(); }
    uint8_t getNumberDeliveredPeople() { return numberDeliveredPeople; }
    bool hasSpace() { return people.size() < MAX_ELEVATOR_PEOPLE; }

    void switchDirection();
    Floor *findNextFloor();
    void advanceFloor();
    void deliverPeople();
    void fillWithPeople();

    bool cycle();
};

#endif

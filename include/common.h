#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <vector>
#include <map>

class Floor;
class Person;

enum ElevatorDirection_t {
    ELEVATOR_DIRECTION_UP,
    ELEVATOR_DIRECTION_DOWN
};

using namespace std;

typedef map<uint8_t, Floor *> FloorMap;
typedef vector<Person *> PeopleVector;

#define MIN_FLOORS 50
#define MAX_FLOORS 100

#define MAX_PEOPLE 25
#define MAX_ELEVATOR_PEOPLE 4

#endif

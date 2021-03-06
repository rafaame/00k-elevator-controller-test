#include "Building.h"
#include "Person.h"
#include "Floor.h"
#include "Elevator.h"

using namespace std;

/**
 * Class constructor.
 */
Building::Building() {
    numberPeople = 0;

    elevator = NULL;
}

/**
 * Class destructor.
 */
Building::~Building() {
    for (auto it = floors.begin(); it != floors.end(); it++) {
        delete it->second;
    }

    floors.clear();

    delete elevator;
}

/**
 * Initializes the building creating floors and randomly populating them with
 * people.
 *
 * @return void
 */
void Building::init() {
    // Initialize the number of floors to an integer between MIN_FLOORS and MAX_FLOORS (constants defined in common.h)
    uint8_t numberFloors = MIN_FLOORS + (rand() % (MAX_FLOORS - MIN_FLOORS + 1));
    numberPeople = 0;

    cout << "Initializing elevator with " << (uint32_t) numberFloors << " floors." << endl;

    // Iterate over the floors populating them
    for (uint8_t i = 0; i < numberFloors; i++) {
        // There is a (theoretically) 50% chance that this floor should have
        // people in it
        bool shouldHavePeople = (bool) (rand() % 2);

        // The number of people in the floor (if it should have any) is an integer
        // between 1 and (MAX_PEOPLE - total people already in the building) / 4,
        // this gives us a better distribution of the number of people in each floor
        uint8_t numberPeopleFloor = shouldHavePeople ? (rand() % ((MAX_PEOPLE - numberPeople) / 4)) : 0;

        numberPeople += numberPeopleFloor;

        cout << "    Initializing floor " << (uint32_t) i << " with " << (uint32_t) numberPeopleFloor << " people." << endl;

        Floor *floor = new Floor(i, numberPeopleFloor);
        floors.insert(make_pair(i, floor));
    }

    // Iterate over people in every floor and assign them random destination floors
    for (auto it = floors.begin(); it != floors.end(); it++) {
        Floor *currentFloor = it->second;

        if (! currentFloor->getNumberWaitingPeople()) {
            continue;
        }

        for (auto pit = currentFloor->getWaitingPeople().begin(); pit != currentFloor->getWaitingPeople().end(); pit++) {
            // The destination floor number should be an integer between 0 and
            // total number of floors in the building
            uint8_t destinationFloorNumber = rand() % numberFloors;

            Person *person = *pit;
            person->setDestinationFloor(floors[destinationFloorNumber]);

            cout << "    Adding person to the floor " << (uint32_t) currentFloor->getNumber() << " whose destination is floor #" << (uint32_t) destinationFloorNumber << endl;
        }
    }

    // Instantiate the elevator with created floors
    elevator = new Elevator(&floors);

    cout << "Total people in the building is " << (uint32_t) numberPeople << endl << endl;
}

/**
 * Run the elevator simulation.
 *
 * @return void
 */
void Building::run() {
    uint64_t numberCycles = 0;
    while (elevator->cycle()) {
        numberCycles++;
    }

    cout << "Finished. Total delivered people: " << (uint32_t) elevator->getNumberDeliveredPeople() << "/" << (uint32_t) numberPeople << endl;
    cout << "Number of elevator cycles: " << (uint32_t) numberCycles << endl;
}

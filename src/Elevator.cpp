#include "Elevator.h"
#include "Person.h"
#include "Floor.h"

using namespace std;

/**
 * Class constructor.
 */
Elevator::Elevator(FloorMap *floors) {
    currentFloor = floors->at(0);
    nextFloor = NULL;
    direction = ELEVATOR_DIRECTION_UP;

    this->floors = floors;

    numberDeliveredPeople = 0;
}

/**
 * Class destructor.
 */
Elevator::~Elevator() {

}

/**
 * Switch elevator direction.
 *
 * @return void
 */
void Elevator::switchDirection() {
    if (direction == ELEVATOR_DIRECTION_UP) {
        direction = ELEVATOR_DIRECTION_DOWN;
    } else {
        direction = ELEVATOR_DIRECTION_UP;
    }
}

/**
 * Finds the elevator next destination floor. This method will try to find the
 * next destination floor for the elevator according to its current direction,
 * to its people destination floor and to the destination floor of people in
 * each floor of the building.
 *
 * Suppose we are in the fifth floor and going up. This method will start
 * iterating in floors above the fifth floor. The floor will be considered the
 * next destination floor if there is someone in the elevator that wants to
 * stay in this floor OR if there is someone in this floor that wants to go to
 * a higher floor. If none of the conditions are met, the next destination floor
 * will be the closest one to our current floor, according to our direction.
 *
 * The same applies if we are going down.
 *
 * @return Floor*
 */
Floor *Elevator::findNextFloor() {
    // If we reached the top or the bottom of the building, there is no next
    // destination floor for this direction
    if ((direction == ELEVATOR_DIRECTION_UP && currentFloor->getNumber() >= getNumberFloors()) ||
        (direction == ELEVATOR_DIRECTION_DOWN && currentFloor->getNumber() <= 0)) {
            return NULL;
    }

    // Define the closest next destination floor in case no optimal next
    // destination floor is found
    Floor *closestFloor = NULL;

    // Start iterating over the floors according to our direction: if we are
    // going up, starts iterating from the floor above up to the top and if we
    // are going down, starts iterating from the floor below up to the bottom.
    int16_t i = (direction == ELEVATOR_DIRECTION_UP) ? (currentFloor->getNumber() + 1) : (currentFloor->getNumber() - 1);
    while ((direction == ELEVATOR_DIRECTION_UP && i < getNumberFloors()) ||
        (direction == ELEVATOR_DIRECTION_DOWN && i >= 0)) {

        Floor *floor = floors->at(i);

        // Find out if someone in the elevator wants to stay in the floor we are
        // iterating. If that's the case, this is the optimal next destination
        // floor
        for (auto it = people.begin(); it != people.end(); it++) {
            Person *person = *it;

            if (person->getDestinationFloor()->getNumber() == floor->getNumber()) {
                return floor;
            }
        }

        // Find out the closes floor with people that wants to go to a higher
        // floor (if we are going up) OR that wants to go to a lower floor (if
        // we are going down).
        if (hasSpace() && floor->getNumberWaitingPeople() > 0) {
            // Iterate over people waiting in the floor we are iterating
            for (auto it = floor->getWaitingPeople().begin(); it != floor->getWaitingPeople().end(); it++) {
                Person *person = *it;

                // If we are going up and this person also wants to go up OR
                // if we are going down and this person also wants to go down,
                // then that's the optimal next destination floor
                if ((direction == ELEVATOR_DIRECTION_UP && person->getDestinationFloor()->getNumber() > floor->getNumber()) ||
                    (direction == ELEVATOR_DIRECTION_DOWN && person->getDestinationFloor()->getNumber() < floor->getNumber())) {
                    return floor;
                }
            }

            // Stores this floor as the closest next destination floor if no
            // optimal next destination floor is found AND no closest floor is
            // already stored
            if (! closestFloor ||
                (direction == ELEVATOR_DIRECTION_UP && floor->getNumber() < closestFloor->getNumber()) ||
                (direction == ELEVATOR_DIRECTION_DOWN && floor->getNumber() < closestFloor->getNumber())) {
                closestFloor = floor;
            }
        }

        // Iterate over the floor above (if we are going up) or over the floor
        // below (if we are going down)
        if (direction == ELEVATOR_DIRECTION_UP) {
            i++;
        } else {
            i--;
        }
    }

    return closestFloor;
}

/**
 * Advance to the next closest floor according to our direction and our current floor.
 *
 * @return void
 */
void Elevator::advanceFloor() {
    // Find the floor above our current floor, if we are not at the top yet
    Floor *floorAbove = NULL;
    if (currentFloor->getNumber() < getNumberFloors() - 1) {
        floorAbove = floors->at(currentFloor->getNumber() + 1);
    }

    // Find the floor below our current floor, if we are not at the bottom yet
    Floor *floorBelow = NULL;
    if (currentFloor->getNumber() > 0) {
        floorBelow = floors->at(currentFloor->getNumber() - 1);
    }

    // Updates the current floor according to our direction
    currentFloor = (direction == ELEVATOR_DIRECTION_UP ? floorAbove : floorBelow);

    cout << "    Current floor updated to #" << (uint32_t) currentFloor->getNumber() << endl;
}

/**
 * Deliver people that wants to stay in the current floor.
 *
 * @return void
 */
void Elevator::deliverPeople() {
    // Iterate over people in the elevator and deliver those whose the
    // destination floor is the current floor
    for (auto it = people.begin(); it != people.end();) {
        Person *person = *it;

        if (person->getDestinationFloor()->getNumber() == currentFloor->getNumber()) {
            currentFloor->deliverPerson(person);
            numberDeliveredPeople++;

            it = people.erase(it);

            cout << "    Delivering person to current floor #" << (uint32_t) currentFloor->getNumber() << endl;
        } else {
            it++;
        }
    }

    cout << "    Delivered " << (uint32_t) numberDeliveredPeople << " people so far, space left in the elevator is " << (uint32_t) (MAX_ELEVATOR_PEOPLE - people.size()) << endl;
}

/**
 * Fills the elevator with people according to its current direction, its current
 * floor and its capacity.
 *
 * This method will attempt to fill the elevator with people that want to go to
 * the same direction its going. If there still some capacity left, more people
 * will be put in the elevator.
 *
 * @return void
 */
void Elevator::fillWithPeople() {
    // Iterate over people waiting in the current floor and get those whose
    // the destination floor is above the current floor and the elevator is going
    // up OR destination floor is below the current floor nad the elevator is
    // going down
    for (auto it = currentFloor->getWaitingPeople().begin(); people.size() < MAX_ELEVATOR_PEOPLE && it != currentFloor->getWaitingPeople().end();) {
        Person *person = *it;

        cout << "    Found waiting person in this floor whose destination floor is #" << (uint32_t) person->getDestinationFloor()->getNumber() << endl;

        if ((person->getDestinationFloor()->getNumber() > currentFloor->getNumber() && direction == ELEVATOR_DIRECTION_UP) ||
            (person->getDestinationFloor()->getNumber() < currentFloor->getNumber() && direction == ELEVATOR_DIRECTION_DOWN)) {
            people.push_back(person);

            it = currentFloor->getWaitingPeople().erase(it);

            cout << "        Destination matches direction (" << direction << "), getting this person. Space left: " << (uint32_t) (MAX_ELEVATOR_PEOPLE - people.size()) << endl;
        } else {
            it++;
        }
    }

    // If there is still space in the elevator, fill it with more people
    for (auto it = currentFloor->getWaitingPeople().begin(); hasSpace() && it != currentFloor->getWaitingPeople().end();) {
        Person *person = *it;

        cout << "    Found waiting person in this floor whose destination floor is #" << (uint32_t) person->getDestinationFloor()->getNumber() << endl;

        people.push_back(person);
        it = currentFloor->getWaitingPeople().erase(it);

        cout << "        Getting another person. Space left: " << (uint32_t) (MAX_ELEVATOR_PEOPLE - people.size()) << endl;
    }
}

/**
 * Elevator simulation cycle. The algorithm is as follows:
 * - Try to find the next destination floor;
 * - Advance to the next floor until we reach out next destination floor;
 * - Once we are in the destination floor, deliver people that wants to stay in
 * this floor and fill the elevator with more people.
 *
 * @return bool  Returns true if another cycle should be run or false otherwise.
 */
bool Elevator::cycle() {
    cout << "Starting elevator cycle" << endl;
    cout << "    Current floor is #" << (uint32_t) currentFloor->getNumber() << " and direction is " << direction << endl;

    nextFloor = findNextFloor();

    if (! nextFloor) {
        switchDirection();
        cout << "    Not found next floor, switching direction to " << direction << endl;

        nextFloor = findNextFloor();
        if (! nextFloor) {
            cout << "    Not found next floor again. Finished." << endl;

            return false;
        }
    }

    cout << "    Next floor is now #" << (uint32_t) nextFloor->getNumber() << endl;

    advanceFloor();

    // We are not in the next destination floor
    if (currentFloor != nextFloor) {
        cout << "    We are not in the next destination floor (#" << (uint32_t) nextFloor->getNumber() << "), skipping..." << endl;

        return true;
    }

    cout << "    We reached the next destination floor" << endl;

    deliverPeople();
    fillWithPeople();

    cout << "Delivered " << (uint32_t) numberDeliveredPeople << " people in this cycle." << endl << endl;

    return true;
}

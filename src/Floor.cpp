#include "Floor.h"
#include "Person.h"

using namespace std;

/**
 * Class constructor.
 *
 * @param uint8_t  number  The floor number.
 */
Floor::Floor(uint8_t number, uint8_t numberPeople) {
    this->number = number;

    for (uint8_t i = 0; i < numberPeople; i++) {
        Person *person = new Person();

        waitingPeople.push_back(person);
    }
}

/**
 * Class destructor.
 */
Floor::~Floor() {
    for (auto it = waitingPeople.begin(); it != waitingPeople.end(); it++) {
        delete *it;
    }

    waitingPeople.clear();
}

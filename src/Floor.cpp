#include "Floor.h"
#include "Person.h"

using namespace std;

/**
 * Class constructor.
 *
 * @param uint8_t  number  The floor number.
 */
Floor::Floor(uint8_t number) {
    this->number = number;
}

/**
 * Class destructor.
 */
Floor::~Floor() {
    clear();
}

/**
 * Initializes the floor with people.
 *
 * @param  uint8_t  numberPeople  The number of people in the floor.
 *
 * @return void
 */
void Floor::init(uint8_t numberPeople) {
    for (uint8_t i = 0; i < numberPeople; i++) {
        Person *person = new Person();

        waitingPeople.push_back(person);
    }
}

/**
 * Clears the floor (deletes all people in the floor).
 *
 * @return void
 */
void Floor::clear() {
    for (auto it = waitingPeople.begin(); it != waitingPeople.end(); it++) {
        delete *it;
    }

    for (auto it = deliveredPeople.begin(); it != deliveredPeople.end(); it++) {
        delete *it;
    }

    waitingPeople.clear();
    deliveredPeople.clear();
}

/**
 * Delivers a person to the floor (add it to the delivered people vector).
 *
 * @param  Person*  person  A pointer to the person to deliver.
 *
 * @return void
 */
void Floor::deliverPerson(Person *person) {
    deliveredPeople.push_back(person);
}

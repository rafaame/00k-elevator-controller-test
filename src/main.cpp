#include "Building.h"

int main(int argc, char** argv) {
    srand(time(NULL));

    Building *building = new Building();
    building->init();
    building->run();

    delete building;
    return 0;
}

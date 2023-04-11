#include "System.hpp"

/*
 * The main function, which initializes the system and runs it.
 */
int main() {
    System* system = new System(684,864);
    system->run();
    delete system;
    return 0;
}

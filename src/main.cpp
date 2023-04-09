#include "System.hpp"

int main() {
    System* system = new System(684,864,12);
    system->run();
    delete system;
    return 0;
}

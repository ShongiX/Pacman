//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include "System.hpp"

int main() {
    System* system = new System(684,864);
    system->run();
    delete system;
    return 0;
}

#include "Window.h"

int main(int argc, char **argv) {
    CS488Window::launch(argc, argv, new Window(), 1024, 768, "CS488 Project");
    return 0;
}

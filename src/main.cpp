#include "Window.h"

int main(int argc, char **argv) {
    Window & window = Window::getInstance();
    window.launch(1024, 768, "Kefka", 60.0f);
    return 0;
}


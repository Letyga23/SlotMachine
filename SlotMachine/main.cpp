#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "Window.h"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    Window window(1000, 600, "Slot Machine");
    window.init();
    window.startMainLoop();
    return 0;
}

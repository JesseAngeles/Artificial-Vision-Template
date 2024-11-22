#include <iostream>

#include "FileController.h"
#include "gui/GUI.h"

using namespace std;

int main()
{
    readFile();

    GUI gui({400, 300}, "titulo");
    gui.drawRectangle({10, 10}, {200, 200}, sf::Color::Transparent, sf::Color::Red);

    gui.mainLoop();

    return 0;
}
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

class GUI
{
private:
    RenderWindow window;
    Vector2i bounds;

    // Conversion
    Vector2f Vector2int2float(Vector2i);
    Vector2i Vector3float2int(Vector2f);

    // Shapes
    std::vector<std::unique_ptr<Drawable>> static_shapes;

public:
    // Constructor
    GUI(Vector2i bounds, const std::string &title);

    // Drawers
    void mainLoop();
    void drawRectangle(Vector2i pos, Vector2f bounds, Color, Color outline_color = Color::Transparent);

    // Getters
    Vector2i getBounds() const { return bounds; }

    // Setters
};

#endif // GUI_H
#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

struct Circle
{
    CircleShape shape;
    std::vector<float> pixel_rgb;
    std::vector<Circle> circles;
};

class GUI
{
private:
    RenderWindow window;
    Vector2u bounds;

    // Image
    Texture image_texture;
    Image image;
    Sprite image_sprite;

    // Conversion
    Vector2f Vector2int2float(Vector2i);
    Vector2i Vector3float2int(Vector2f);

    // Shapes
    std::vector<std::unique_ptr<Drawable>> static_shapes;
    std::vector<Circle> circles;

public:
    // Constructor
    GUI(const std::string &title, const std::string &image_route);

    // Drawers
    void mainLoop();
    void drawRectangle(Vector2i pos, Vector2f bounds, Color, Color outline_color = Color::Transparent);
    void drawCircle(Vector2i pos, float radius, Color color);

    // Functions
    std::vector<float> getPixelColor(Vector2i pos);

    // Getters
    Vector2u getBounds() const { return bounds; }
    std::vector<Circle>& getCircles() { return circles; }

    // Setters
    void setCircles(std::vector<Circle> circles) { this->circles = circles; }
};

#endif // GUI_H
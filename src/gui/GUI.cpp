#include "gui/GUI.h"

GUI::GUI(const std::string &title, const std::string &image_route)
{
    if (!image_texture.loadFromFile(image_route))
    {
        window.close();
        return;
    }

    bounds = image_texture.getSize(); // Obtiene las dimensiones de la imagen

    // Crear la ventana
    window.create(sf::VideoMode(bounds.x, bounds.y), title, Style::Close);

    // Configurar el sprite con la textura cargada
    image_sprite.setTexture(image_texture);
    image = image_texture.copyToImage();
}

void GUI::mainLoop()
{
    Clock clock;
    float delta_time;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);
                return;
            }

            delta_time += clock.restart().asMilliseconds();

            window.clear();

            window.draw(image_sprite);

            // draw static elements
            for (const auto &shape : static_shapes)
                window.draw(*shape);

            for (Circle circle : circles)
                window.draw(circle.shape);

            window.display();
        }
    }
}

// Drawers
void GUI::drawRectangle(Vector2i pos, Vector2f bounds, Color color, Color outline_color)
{
    auto rectangle = std::make_unique<RectangleShape>(bounds);
    rectangle->setPosition(pos.x, pos.y);
    rectangle->setFillColor(color);
    rectangle->setOutlineThickness(2);
    rectangle->setOutlineColor(outline_color);

    static_shapes.push_back(std::move(rectangle));
}

void GUI::drawCircle(Vector2i pos, float radius, Color color)
{
    CircleShape circle_shape(radius);
    circle_shape.setPosition(pos.x - radius, pos.y - radius);
    circle_shape.setFillColor(color);

    Circle circle;
    circle.shape = circle_shape;
    circle.pixel_rgb = getPixelColor(pos);

    this->circles.push_back(circle);
}

std::vector<float> GUI::getPixelColor(Vector2i pos)
{
    if (pos.x < 0 || pos.x >= bounds.x || pos.y < 0 || pos.y >= bounds.y)
        return {0.0f, 0.0f, 0.0f}; 

    Color color = image.getPixel(pos.x, pos.y);

    std::vector<float> rgb = {
        static_cast<float>(color.r),
        static_cast<float>(color.g),
        static_cast<float>(color.b)};

    return rgb;
}
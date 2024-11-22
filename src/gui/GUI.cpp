#include "gui/GUI.h"

GUI::GUI(Vector2i bounds, const std::string &title)
    : bounds(bounds)
{
    window.create(VideoMode(bounds.x, bounds.y), title, Style::Close);
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
            }

            delta_time += clock.restart().asMilliseconds();

            window.clear();

            // draw static elements
            for (const auto &shape : static_shapes)
                window.draw(*shape);

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
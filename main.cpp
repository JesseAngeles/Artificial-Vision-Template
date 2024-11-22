#include <iostream>

#include "FileController.h"
#include "gui/GUI.h"

#include "clustering/AHC.h"
#include "Randomizer.h"

using namespace std;

int main()
{
    int points;

    GUI gui("image", readFile("./resources/images/*", {"*.png", "*.jpg", "*.bmp"}));

    cout << "Points: ";
    cin >> points;

    for (int i = 0; i < points; i++)
    {
        int x = randomInt(0, gui.getBounds().x);
        int y = randomInt(0, gui.getBounds().y);

        gui.drawCircle({x, y},
                       5,
                       {static_cast<sf::Uint8>(randomInt(0, 255)),
                        static_cast<sf::Uint8>(randomInt(0, 255)),
                        static_cast<sf::Uint8>(randomInt(0, 255))});
    }

    vector<vector<float>> data;
    for (Circle circle : gui.getCircles())
        data.push_back(circle.pixel_rgb);

    AHC ahc(data);
    ahc.displayClusters();

    while (ahc.getClusters().size() > 1)
    {
        ahc.displayClusters();
        ahc.mergeStep(true);

        // Accede a los círculos directamente de la clase GUI
        std::vector<Circle> &circles = gui.getCircles(); // Nota: cambia a un getter que devuelva referencia

        for (const auto &cluster : ahc.getClusters())
        {
            Color color(
                static_cast<sf::Uint8>(randomInt(0, 255)),
                static_cast<sf::Uint8>(randomInt(0, 255)),
                static_cast<sf::Uint8>(randomInt(0, 255)));

            for (const auto &point : cluster.points)
            {
                for (auto &circle : circles) // Nota: usa referencia aquí
                {
                    if (circle.pixel_rgb == point)
                    {
                        circle.shape.setFillColor(color);
                    }
                }
            }
        }

        gui.setCircles(circles); // Aunque esto no es necesario porque ya modificaste el vector original

        gui.mainLoop();
    }

    gui.mainLoop();

    exportToJsonAHC(ahc.getMergeHistory(), "dendrogram_data.json");
    int result = std::system("python python/AHC.py");

    return 0;
}
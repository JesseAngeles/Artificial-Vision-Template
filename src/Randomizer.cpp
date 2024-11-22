#include "Randomizer.h"

std::random_device rd;
std::mt19937 engine(rd()); // Inicialización del generador con una semilla única

int randomInt(int min, int max)
{
    if (min > max)
        std::swap(min, max);

    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(engine);
}
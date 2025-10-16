
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>

#include "node.hpp"

const int WINDOW_SIZE = 800;

// void initGrid(){}
// void drawGrid(){}
// void aStar(){}

int main()
{
    sf::Window window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "My window");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
    }
}

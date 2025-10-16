
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>

#include "node.hpp"

const float WINDOW_SIZE = 800;
const float NODES_PER_ROW_COL = 20;

void initNeigbours(std::vector<std::vector<Node>> &grid);
void drawGrid(sf::RenderWindow &window);
// void aStar(){}

int main()
{
    // Initialize grid
    std::vector<std::vector<Node>> grid(NODES_PER_ROW_COL, std::vector<Node>(NODES_PER_ROW_COL));
    initNeigbours(grid);

    // Create Window
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "My window");
    sf::Clock clock;
    window.setFramerateLimit(60);

    // Loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw everything


        
        drawGrid(window);

        // Update the window
        window.display();
    }
}

void drawGrid(sf::RenderWindow &win){
    // Draw horizontal lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({WINDOW_SIZE, 1.f});
        line.setPosition({0.f, (WINDOW_SIZE/NODES_PER_ROW_COL)*i - 0.5});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }

    // Draw vertical lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({1.f, WINDOW_SIZE});
        line.setPosition({(WINDOW_SIZE/NODES_PER_ROW_COL)*i - 0.5, 0.f});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }
}

void initNeigbours(std::vector<std::vector<Node>> &grid){
    for(int i = 0; i < NODES_PER_ROW_COL; i++){
        for(int j = 0; j < NODES_PER_ROW_COL; j++){
            if (i > 0) { grid[i][j].neighbors.push_back(&grid[i-1][j]);}
            if (i < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i+1][j]);}
            if (j > 0) {grid[i][j].neighbors.push_back(&grid[i][j-1]);}
            if (j < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i][j+1]);}
        }
    }

}


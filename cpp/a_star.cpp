
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>

#include "node.hpp"

const float WINDOW_SIZE = 800;
const float NODES_PER_ROW_COL = 20;
const float NODE_SIZE = WINDOW_SIZE/NODES_PER_ROW_COL;

void initNeighboursAndPos(std::vector<std::vector<Node>> &grid);
void drawGrid(sf::RenderWindow &window);
void drawNodes(std::vector<std::vector<Node>> &grid, sf::RenderWindow &win);
// void aStar(){}

int main()
{
    // Initialize grid
    std::vector<std::vector<Node>> grid(NODES_PER_ROW_COL, std::vector<Node>(NODES_PER_ROW_COL));
    initNeighboursAndPos(grid);

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
        drawNodes(grid, window);
        drawGrid(window);

        // Update the window
        window.display();
    }
}

void initNeighboursAndPos(std::vector<std::vector<Node>> &grid){
    for(int i = 0; i < NODES_PER_ROW_COL; i++){
        for(int j = 0; j < NODES_PER_ROW_COL; j++){
            grid[i][j].x = i;
            grid[i][j].y = j;
            if (i > 0) { grid[i][j].neighbors.push_back(&grid[i-1][j]);}
            if (i < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i+1][j]);}
            if (j > 0) {grid[i][j].neighbors.push_back(&grid[i][j-1]);}
            if (j < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i][j+1]);}
        }
    }
}

void drawGrid(sf::RenderWindow &win){
    // Draw horizontal lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({WINDOW_SIZE, 1.f});
        line.setPosition({0.f, (NODE_SIZE)*i - 0.5});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }

    // Draw vertical lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({1.f, WINDOW_SIZE});
        line.setPosition({(NODE_SIZE)*i - 0.5, 0.f});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }
}

void drawNodes(std::vector<std::vector<Node>> &grid, sf::RenderWindow &win){
    // Draw squares representing Nodes
    for(auto &row : grid) {
        for(auto Node : row){
            sf::RectangleShape rectangle({NODE_SIZE, NODE_SIZE});
            rectangle.setPosition({Node.x * NODE_SIZE, Node.y * NODE_SIZE});

            switch (Node.type) {
                case NodeType::Empty : rectangle.setFillColor(sf::Color::White); break;
                case NodeType::Wall : rectangle.setFillColor(sf::Color::Black); break;
                case NodeType::Start : rectangle.setFillColor(sf::Color::Green); break;
                case NodeType::End : rectangle.setFillColor(sf::Color::Red); break;
                case NodeType::Path : rectangle.setFillColor(sf::Color::Blue); break;
                case NodeType::Open : rectangle.setFillColor(sf::Color::Yellow); break;
                case NodeType::Closed : rectangle.setFillColor(sf::Color::Cyan); break;

            win.draw(rectangle);
            }
        }
    }
}



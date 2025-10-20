
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include <string>
#include <vector>

#include "node/node.hpp"

constexpr float WINDOW_SIZE = 800;
constexpr float NODES_PER_ROW_COL = 20;
constexpr float NODE_SIZE = WINDOW_SIZE/NODES_PER_ROW_COL;

std::vector<std::vector<Node>> initNeighboursAndPos(); //todo: split to initNeighboors and initPos
void drawGrid(sf::RenderWindow &window);
void drawNodes(const std::vector<std::vector<Node>> &grid, sf::RenderWindow &win);
void paintNode(std::vector<std::vector<Node>> &grid, bool &startExist, bool &endExist, int nodeX, int nodeY);
void clearNode(std::vector<std::vector<Node>> &grid, bool &startExist, bool &endExist, int nodeX, int nodeY);
// void aStar(){}
// void resetGrid

int main()
{
    // Initialize grid
    auto grid = initNeighboursAndPos();
    bool startExist = false;
    bool endExist = false;

    // Create Window
    sf::RenderWindow window(sf::VideoMode({(int)WINDOW_SIZE, (int)WINDOW_SIZE}), "My window");
    sf::Clock clock;
    window.setFramerateLimit(60);

    // Loop
    while (window.isOpen()){
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Paint node on left mouse click
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            // Get global mouse position
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if ((position.x > 0) && (position.x < WINDOW_SIZE) && (position.y > 0) && (position.y < WINDOW_SIZE)){
                int nodeX = position.x / NODE_SIZE;
                int nodeY = position.y / NODE_SIZE;
                if (grid[nodeX][nodeY].type == NodeType::Empty){
                    paintNode(grid, startExist, endExist, nodeX, nodeY);
                }
            }
        }
        // Clear node on right mouse click
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            // Get global mouse position
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if ((position.x > 0) && (position.x < WINDOW_SIZE) && (position.y > 0) && (position.y < WINDOW_SIZE)){
                int nodeX = position.x / NODE_SIZE;
                int nodeY = position.y / NODE_SIZE;
                if (grid[nodeX][nodeY].type != NodeType::Empty){
                    clearNode(grid, startExist, endExist, nodeX, nodeY);
                }
            }
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

std::vector<std::vector<Node>> initNeighboursAndPos(){
    std::vector<std::vector<Node>> grid(NODES_PER_ROW_COL, std::vector<Node>(NODES_PER_ROW_COL));
    for(int i = 0; i < NODES_PER_ROW_COL; i++){
        for(int j = 0; j < NODES_PER_ROW_COL; j++){
            grid[i][j].x = i;
            grid[i][j].y = j;
            if (i > 0) { grid[i][j].neighbors.push_back(&grid[i-1][j]);}
            if (i < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i+1][j]);} //todo: move do separate func
            if (j > 0) {grid[i][j].neighbors.push_back(&grid[i][j-1]);}
            if (j < NODES_PER_ROW_COL-2) {grid[i][j].neighbors.push_back(&grid[i][j+1]);}
            }
        }
        return grid;
    }


void drawGrid(sf::RenderWindow &win){ // change name to init stripes or smth
    // Draw horizontal lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({WINDOW_SIZE, 1.f});
        line.setPosition({0.f, (NODE_SIZE)*i - 0.5f});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }

    // Draw vertical lines
    for(int i = 0; i <= NODES_PER_ROW_COL; i++){
        sf::RectangleShape line({1.f, WINDOW_SIZE});
        line.setPosition({(NODE_SIZE)*i - 0.5f, 0.f});
        line.setFillColor(sf::Color(125, 125, 125));
        win.draw(line);
    }
}

void drawNodes(const std::vector<std::vector<Node>> &grid, sf::RenderWindow &win){
    // Draw squares representing Nodes
    for(auto &row : grid) {
        for(auto &Node : row){
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
            }
             win.draw(rectangle);
        }
    }
}

void paintNode(std::vector<std::vector<Node>> &grid, bool &startExist, bool &endExist, int nodeX, int nodeY){
    if (!startExist) {grid[nodeX][nodeY].type = NodeType::Start; startExist = true;}
    else if (!endExist) {grid[nodeX][nodeY].type = NodeType::End; endExist = true;}
    else {grid[nodeX][nodeY].type = NodeType::Wall;}
}

void clearNode(std::vector<std::vector<Node>> &grid, bool &startExist, bool &endExist, int nodeX, int nodeY){
    if (grid[nodeX][nodeY].type == NodeType::Start) {grid[nodeX][nodeY].type = NodeType::Empty; startExist = false;}
    else if (grid[nodeX][nodeY].type == NodeType::End) {grid[nodeX][nodeY].type = NodeType::Empty; endExist = false;}
    else {grid[nodeX][nodeY].type = NodeType::Empty;}
}


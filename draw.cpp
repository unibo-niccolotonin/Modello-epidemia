#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.hpp"
#include "board_functions.hpp"
#include <array>
#include <cmath>

void draw (sf::RenderWindow& window, Board const& board, std::vector<std::array<int, 4> >& graph)
{
    float x = 0.f;
    float y = 0.f;
        
    double n_susceptible = 0;
    double n_infected = 0;
    double n_immune = 0;
    double n_dead = 0;

    sf::RectangleShape cell_square(sf::Vector2f(board.cell_length, board.cell_length));
    cell_square.setPosition(sf::Vector2f(x, y));
    
    for (int i = 0; i < board.get_size(); i++)
    {
        for (int j = 0; j < board.get_size(); j++)
        {
            switch(board(i, j).status)
            {
                case state::non_existant:
                    cell_square.setFillColor(sf::Color(30,30,30,255)); //Black
                    break;
                case state::susceptible:
                    cell_square.setFillColor(sf::Color(54, 42, 201, 255)); //Blue
                    n_susceptible++;
                    break;
                case state::infected:
                    cell_square.setFillColor(sf::Color(209, 26, 29, 255)); //Red
                    n_infected++;
                    break;
                case state::immune:
                    cell_square.setFillColor(sf::Color(43, 229, 6, 255)); //Green
                    n_immune++;
                    break;
                case state::dead:
                    cell_square.setFillColor(sf::Color(111, 111, 111, 255)); //Gray
                    n_dead++;
                    break;
            }
            cell_square.setPosition(sf::Vector2f(x, y));
            window.draw(cell_square);

            x += board.cell_length;
        }
        y += board.cell_length;
        x = 0.f;
    }
    
    //Disegna il grafico relativo alle proporzioni degli stati delle cellule
    
    int n_total = n_susceptible + n_immune + n_infected + n_dead;
    
    int height_susceptible = std::round(n_susceptible / n_total * board.graph_height);
    int height_immune = height_susceptible + std::round(n_immune / n_total * board.graph_height);
    int height_dead = height_immune + std::round(n_dead / n_total * board.graph_height);
    int height_infected = board.graph_height;
    
    if (graph.size() * board.graph_column_width <= window.getSize().x)
    {
        std::array<int, 4> arr = {height_infected, height_dead, height_immune, height_susceptible};
        graph.push_back(arr);
    }
    
    
    for (int i = 0; i < graph.size(); i++)
    {
        sf::RectangleShape column_Infected(sf::Vector2f(board.graph_column_width, graph[i][0]));
        sf::RectangleShape column_Dead(sf::Vector2f(board.graph_column_width, graph[i][1]));
        sf::RectangleShape column_Immune(sf::Vector2f(board.graph_column_width, graph[i][2]));
        sf::RectangleShape column_Susceptible(sf::Vector2f(board.graph_column_width, graph[i][3]));
        
        column_Susceptible.setPosition(i * board.graph_column_width, board.get_size() * board.cell_length);
        column_Infected.setPosition(i * board.graph_column_width, board.get_size() * board.cell_length);
        column_Immune.setPosition(i * board.graph_column_width, board.get_size() * board.cell_length);
        column_Dead.setPosition(i * board.graph_column_width, board.get_size() * board.cell_length);
        
        column_Dead.setFillColor(sf::Color(111, 111, 111, 255));
        column_Immune.setFillColor(sf::Color(43, 229, 6, 255));
        column_Infected.setFillColor(sf::Color(209, 26, 29, 255));
        column_Susceptible.setFillColor(sf::Color(54, 42, 201, 255));
        
        window.draw(column_Infected);
        window.draw(column_Dead);
        window.draw(column_Immune);
        window.draw(column_Susceptible);
    }
}

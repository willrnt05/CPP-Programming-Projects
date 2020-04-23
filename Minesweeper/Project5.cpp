#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Board.h"

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper!");
    

    sf::Texture hidTile;

    hidTile.loadFromFile("images/tile_hidden.png");

    sf::Sprite hiddenTile(hidTile);

    Board B;
    //B.SetBoard("boards/testboard1.brd");
    B.SetRandomBoard();
    //HERE
    B.debugMode = false;
    


    while (window.isOpen())
    {
        sf::Event event;

        window.clear(sf::Color::White);

        bool presetBlanks = B.StandAloneEmpties(B);

        while (presetBlanks == true)
        {
            presetBlanks = B.StandAloneEmpties(B);
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);


        int arrayX = (int)mousePosition.x / 32 + 1;
        int arrayY = (int)mousePosition.y / 32 + 1;
      
        B.PrintMineCount(window);


        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    B.LeftClickTile(mousePosition.x, mousePosition.y);
                    //cout << "Got a left click @ x: " << mousePosition.x << " y: " << mousePosition.y << endl;
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    B.FlagTile(arrayX, arrayY);
                    //cout << "Got a right click @ x: " << arrayX << " y: " << arrayY << endl;
                }
            }
        }



        window.clear();
       
        B.PrintBoard(window);

        window.display();
    }

    return 0;
}
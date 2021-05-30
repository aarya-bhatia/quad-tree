#include "Quad.h"
#include "AABB.h"
#include "Range.h"

#include <SFML/Window/Event.hpp>

#define width 1600
#define height 1200
#define title "QuadTree"

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    Quad *qtree = Quad::createQtree(window);

    srand(time(0));

    int t = 2;
    bool adding = true;

    Range range(200, 300, 400, 400);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Window close event
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Resize window event
            else if (event.type == sf::Event::Resized)
            {
                delete qtree;
                qtree = Quad::createQtree(window);
            }

            ///
            // Key Events->
            // Esc: Close window
            // I: Print total points
            // P: Toggle add points
            ///
            else if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;

                case sf::Keyboard::I:
                    std::cout << "points count = " << Quad::count << std::endl;
                    break;

                case sf::Keyboard::P:
                    adding = !adding;
                    break;
                default:
                    break;
                }
            }

            // Mouse click
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // Reposition range to mouse position and unmark currently marked points
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (range.isMarked())
                    {
                        range.setMarked(false);
                        qtree->query(range);
                    }

                    std::cout << "Repositioning the range..." << std::endl;
                    range.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                    std::cout << range.boundary.x << "," << range.boundary.y << std::endl;
                    std::cout << range.boundary.shape.getPosition().x << "," << range.boundary.shape.getPosition().y << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);

        if (qtree == nullptr)
            continue;

        t = (t + 1) % INT16_MAX;

        // Insert point into quad tree every 120 frames when adding flag is true
        if (adding && t % 120 == 0)
        {
            sf::Vector2i p = sf::Mouse::getPosition(window);
            qtree->insert(sf::Vector2f(p));
        }

        // Mark all points in range through the quad tree
        if (!range.isMarked())
        {
            range.setMarked(true);
        }
        qtree->query(range);

        // Render everything

        qtree->render(window);
        range.render(window);

        // Buffer swap
        window.display();
    }

    // Cleanup
    delete qtree;

    return 0;
}
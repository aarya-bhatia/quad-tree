#include <SFML/Window/Event.hpp>
#include "Quad.h"
#include "AABB.h"
#include "Range.h"

static const float width = 1600;
static const float height = 1200; 
static const char *title = "Quad Tree";


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    Quad *qtree = new Quad(AABB(sf::Vector2f(), sf::Vector2f(window.getSize()), sf::Color::Yellow), 0);

    srand(time(0));

    int t = 0;
    bool adding = true;
    int dsize = 5;
    long points = 0;

    Range range(0, 0, 200, 200);

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
                bool tmp = adding;
                adding = false;
                points = 0;
                delete qtree;
                qtree = Quad::createQtree(window);
                std::cout << "New window size: " << sf::Vector2f(window.getSize()) << std::endl;
                adding = tmp;
            }

            ///
            // Key Events->
            // Esc: Close window
            // C: Clear all points
            // I: Print total points
            // P: Toggle play/pause adding points
            // S: Toogle show/hide points
            // G: Toggle show/hide grid
            ///
            else if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                
                case sf::Keyboard::C:
                    delete qtree;
                    qtree = Quad::createQtree(window);
                    points = 0;

                case sf::Keyboard::I:
                    std::cout << "Total points: " << points << std::endl;
                    break;

                case sf::Keyboard::P:
                    adding = !adding;
                    break;

                case sf::Keyboard::S:
                    Quad::showPoints = !Quad::showPoints;
                    break;
                
                case sf::Keyboard::G:
                    Quad::showGrid = !Quad::showGrid;

                default:
                    break;
                }
            }

            // Modify boundary size
            else if (event.type == sf::Event::KeyPressed)
            {
                range.setMarked(false);
                qtree->query(range);

                switch (event.key.code)
                {
                case sf::Keyboard::Down:
                    range.setHeight(range.getHeight() - dsize);
                    break;

                case sf::Keyboard::Up:
                    range.setHeight(range.getHeight() + dsize);
                    break;
                
                case sf::Keyboard::Left:
                    range.setWidth(range.getWidth() - dsize);
                    break;

                case sf::Keyboard::Right:
                    range.setWidth(range.getWidth() + dsize);
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
                    range.setMarked(false);
                    qtree->query(range);
                    range.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
                }
            }
        }

        window.clear(sf::Color::Black);

        t = (t + 1) % INT32_MAX;

        // Insert point into quad tree every 120 frames when adding flag is true
        if (adding && t % 120 == 0)
        {
            sf::Vector2f point = sf::Vector2f(sf::Mouse::getPosition(window));

            if(qtree && qtree->insert(point))
            {
                points++;
            }
            else
            {
                std::cout << "Failed to insert point: " << point << std::endl;
            }
        }

        // Mark all points in range through the quad tree
        if (!range.isMarked())
        {
            range.setMarked(true);
        }

        if(qtree)
        {
            qtree->query(range); // Query new points
            qtree->render(window);
        }

        range.render(window);

        window.display(); // Buffer swap
    }

    // Cleanup
    delete qtree;

    return 0;
}
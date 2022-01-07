#include <SFML/Window/Event.hpp>
#include "Quad.h"
#include "AABB.h"
#include "Range.h"

static const float width = 1600;
static const float height = 1200; 
static const char *title = "QuadTree";


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), title);
    Quad *qtree = new Quad(AABB(sf::Vector2f(), sf::Vector2f(window.getSize()), sf::Color::Yellow));

    srand(time(0));

    int t = 2;
    bool adding = true;
    int dsize = 2;

    Range range(0, 0, 400, 400);

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
            // P: Toggle play/pause adding points
            // S: Toogle show/hide points
            ///
            else if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    break;

                case sf::Keyboard::I:
                    std::cout << "Total points: " << qtree->count << std::endl;
                    break;

                case sf::Keyboard::P:
                    adding = !adding;
                    break;

                case sf::Keyboard::S:
                    qtree->showPoints = !qtree->showPoints;
                    break;

                default:
                    break;
                }
            }

            // Modify boundary size
            else if (event.type == sf::Event::KeyPressed)
            {
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
                    if (range.isMarked())
                    {
                        range.setMarked(false);
                        qtree->query(range);
                    }

                    range.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));
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

        // Query new points
        qtree->query(range);

        // Render
        qtree->render(window);
        range.render(window);

        // Buffer swap
        window.display();
    }

    // Cleanup
    delete qtree;

    return 0;
}
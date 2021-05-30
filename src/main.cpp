#include "Quad.h"
#include "AABB.h"
#include "Range.h"

#include <SFML/Window/Event.hpp>

Quad *createQtree(sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    return new Quad(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(size));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Quadtree");
    Quad *qtree = createQtree(window);

    srand(time(0));

    int t = 0;
    bool adding = false;

    Range r(200, 300, 400, 400);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                delete qtree;
                qtree = createQtree(window);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Q)
                {
                    r.query(*qtree);
                }
                else if (event.key.code == sf::Keyboard::I)
                {
                    std::cout << "points count = " << Quad::count << std::endl;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    adding = !adding;
                    std::cout << "Adding: " << adding << std::endl;
                }
            }
        }

        window.clear(sf::Color::Black);

        t = (t + 1) % INT16_MAX;

        if (adding && t % 120 == 0)
        {
            sf::Vector2i p = sf::Mouse::getPosition(window);
            qtree->insert(sf::Vector2f(p));
        }

        qtree->render(window);

        r.render(window);

        window.display();
    }

    delete qtree;

    return 0;
}
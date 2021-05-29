#include "Quad.h"
#include "AABB.h"

#include <SFML/Window/Event.hpp>

std::unique_ptr<Quad> createQtree(sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    return std::make_unique<Quad>(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(size));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1200), "Quadtree", sf::Style::Default);
    std::unique_ptr<Quad> qtree = createQtree(window);

    srand(time(0));
    int t = 0;
    bool adding = true;

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
                qtree.release();
                qtree = createQtree(window);
            }
            else if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                adding = !adding;
            }
        }

        window.clear(sf::Color::Black);

        t = (t + 1) % INT16_MAX;

        if (adding && t % 60 == 0)
        {
            qtree->insert(sf::Vector2f(sf::Mouse::getPosition(window)));
        }

        qtree->render(window);

        window.display();
    }
    return 0;
}
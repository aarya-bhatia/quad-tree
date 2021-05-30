#pragma once

#include <SFML/Graphics.hpp>

static const int radius = 2;
static const sf::Color marked = sf::Color::Red;
static const sf::Color normal = sf::Color::White;

class Point
{
public:
    explicit Point(const sf::Vector2f &point = sf::Vector2f())
    {
        shape = sf::CircleShape(radius);
        shape.setFillColor(normal);
        shape.setPosition(point);
    }

    const sf::Vector2f &position() const
    {
        return shape.getPosition();
    }

    void mark()
    {
        shape.setFillColor(marked);
    }

    void unmark()
    {
        shape.setFillColor(normal);
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(shape);
    }

private:
    sf::CircleShape shape;
};
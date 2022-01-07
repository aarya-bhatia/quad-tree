#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Point
{
public:
    explicit Point(const sf::Vector2f &position = sf::Vector2f());

    const sf::Vector2f &position() const;
    void mark();
    void unmark();
    void render(sf::RenderWindow &window);

    static const int radius;
    static const sf::Color marked;
    static const sf::Color normal;

private:
    sf::CircleShape shape_;
};

std::ostream &operator<<(std::ostream &out, const sf::Vector2f &point);
std::ostream &operator<<(std::ostream &out, const Point &point);
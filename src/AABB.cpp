#include "AABB.h"

void AABB::init()
{
    shape = sf::RectangleShape();
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(4);
    shape.setOutlineColor(color);
    shape.setPosition(x - hw, y - hh); // Top left corner
    shape.setSize(sf::Vector2f(hw * 2, hh * 2));
}
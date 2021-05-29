#include "AABB.h"

void AABB::init()
{
    shape.setPosition(x - hw, y - hh); // Top left corner
    shape.setSize(sf::Vector2f(hw * 2, hh * 2));
    shape.setOutlineThickness(4);
    shape.setOutlineColor(sf::Color::White);
    shape.setFillColor(sf::Color::Black);
    // std::cout << "AABB: " << x - hw << ", " << y - hh << ", " << 2 * hw << ", " << 2 * hh << std::endl;
}
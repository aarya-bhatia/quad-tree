#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <iostream>

// Axis aligned bounding box
struct AABB
{
    float x;  //center x
    float y;  // center y
    float hw; // half width
    float hh; // half height

    sf::RectangleShape shape;

    explicit AABB(float x = 0, float y = 0, float width = 0, float height = 0) : x(x), y(y), hw(width / 2), hh(height / 2), shape()
    {
        init();
    }

    void init();

    ///
    // checks whether this box contains the given point
    ///
    bool contains(const sf::Vector2f &point) const
    {
        return point.x >= x - hw &&
               point.y >= y - hh &&
               point.x <= x + hw &&
               point.y <= y + hh;
    }

    ///
    // checks whether the other box intersects with this box.
    // It cannot intersect if the left edge of other box is ahead of the right edge of this box.
    // It cannot intersect if the right edge of other box is behind the left edge of this box.
    // It cannot intersect if the bottom edge of other box is above the top edge of this box.
    // It cannot intersect if the top edge of other box is below the bottom edge of this box.
    // If any of these conditions are true, we return false.
    ///
    bool intersects(const AABB &other) const
    {
        return !(other.x - other.hw > x + hw ||
                 other.x + other.hw < x - hw ||
                 other.y + other.hh < y - hh ||
                 other.y - other.hh > y + hh);
    }

    // returns the top right quad of this region
    AABB northeast() const
    {
        return AABB(x + hw / 2, y - hh / 2, hw, hh);
    }

    // returns the top left quad of this region
    AABB northwest() const
    {
        return AABB(x - hw / 2, y - hh / 2, hw, hh);
    }

    // returns the bottom left quad of this region
    AABB southwest() const
    {
        return AABB(x - hw / 2, y + hh / 2, hw, hh);
    }

    // returns the bottom right quad of this region
    AABB southeast() const
    {
        return AABB(x + hw / 2, y + hh / 2, hw, hh);
    }

    // checks if the point lies in the NE quadrant of box
    bool isNE(const sf::Vector2f &point) const
    {
        return point.x >= x && point.y <= y;
    }

    // checks if the point lies in the NW quadrant of box
    bool isNW(const sf::Vector2f &point) const
    {
        return point.x <= x && point.y <= y;
    }

    // checks if the point lies in the SE quadrant of box
    bool isSE(const sf::Vector2f &point) const
    {
        return point.x >= x && point.y >= y;
    }

    // checks if the point lies in the SW quadrant of box
    bool isSW(const sf::Vector2f &point) const
    {
        return point.x <= x && point.y >= y;
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};
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
    sf::Color color; //outline

    explicit AABB(float x_ = 0, float y_ = 0, float width_ = 0, float height_ = 0, const sf::Color &color_ = sf::Color::White)
    {
        x = x_;
        y = y_;
        hw = width_ / 2;
        hh = height_ / 2;
        color = color_;

        init();
    }

    explicit AABB(const sf::Vector2f &center, const sf::Vector2f &size)
    {
        x = center.x;
        y = center.y;
        hw = size.x/2;
        hh = size.y/2;
        color = sf::Color::White;

        init();
    }

    void init();

    float getHeight() const 
    {
        return hh * 2;
    }

    float getWidth() const 
    {
        return hw * 2;
    }

    void setWidth(float nw)
    {
        if(nw <= 0) return;

        hw = nw/2;

        x = shape.getPosition().x + hw;
        y = shape.getPosition().y + hh;

        shape.setPosition(x - hw, y - hh);
        shape.setSize(sf::Vector2f(hw * 2, hh * 2));
    }

    void setHeight(float nh)
    {
        if(nh <= 0) return;

        hh = nh/2;

        x = shape.getPosition().x + hw;
        y = shape.getPosition().y + hh;

        shape.setPosition(x - hw, y - hh);
        shape.setSize(sf::Vector2f(hw * 2, hh * 2));
    }

    void setPosition(const sf::Vector2f &position)
    {
        x = position.x + hw;
        y = position.y + hh;

        shape.setPosition(x - hw, y - hh);
        shape.setSize(sf::Vector2f(hw * 2, hh * 2));
    }

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

    bool contains(float x, float y) const 
    {
        return contains(sf::Vector2f(x, y));
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
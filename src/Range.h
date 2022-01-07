#pragma once

#include "AABB.h"

class Range
{
private:
    bool marked = false;

public:
    AABB boundary;
    int num_points = 0;

    Range(float x, float y, float w, float h) : boundary(x, y, w, h, sf::Color::Green)
    {
    }

    void setWidth(float width)
    {
        boundary.setWidth(width);
    }

    void setHeight(float height)
    {
        boundary.setHeight(height);
    }

    bool isMarked() const
    {
        return marked;
    }

    void setMarked(bool b)
    {
        num_points = 0;
        marked = b;
    }

    void render(sf::RenderWindow &window)
    {
        boundary.render(window);
    }

    void setPosition(const sf::Vector2f &position)
    {
        boundary.setPosition(position);
    }
};
#pragma once

#include "AABB.h"
#include "Quad.h"

struct Range
{
    AABB range;
    sf::RectangleShape shape;

    bool marked = false;

    Range(float x, float y, float w, float h) : range(x, y, w, h)
    {
        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(sf::Vector2f(x - w / 2, y - h / 2));
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(4);
    }

    void update()
    {
        marked = !marked;
    }

    void query(Quad &quad)
    {
        update();
        quad.query(range, marked);
    }

    void render(sf::RenderWindow &window)
    {
        window.draw(shape);
    }
};
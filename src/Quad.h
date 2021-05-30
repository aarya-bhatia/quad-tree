#pragma once

#include "AABB.h"
#include "QtNode.h"
#include "Range.h"

#include <iostream>
#include <array>

enum quadrants
{
    northeast,
    southeast,
    southwest,
    northwest
};

// The quad class is a 4-ary tree, which represents the subdivisons of 2D space.
class Quad
{
public:
    Quad(const AABB &boundary = AABB()) : boundary(boundary), node()
    {
        for (int i = 0; i < 4; i++)
        {
            children[i] = nullptr;
        }
    }

    Quad(const sf::Vector2f &center, const sf::Vector2f &size) : Quad(AABB(center.x, center.y, size.x, size.y)) {}

    ~Quad()
    {
        clear();
    }

    bool insert(const sf::Vector2f &point);
    void query(const Range &range);
    void render(sf::RenderWindow &window);

    static int count;

    static Quad *createQtree(const sf::RenderWindow &window)
    {
        sf::Vector2u size = window.getSize();
        return new Quad(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(size));
    }

private:
    AABB boundary;
    QtNode node;
    Quad *children[4];

    void clear();
};

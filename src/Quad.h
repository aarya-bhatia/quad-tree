#pragma once

#include "AABB.h"
#include "QtNode.h"

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
    Quad(const AABB &boundary = AABB()) : boundary(boundary), node() {}

    Quad(const sf::Vector2f &center, const sf::Vector2f &size) : Quad(AABB(center.x, center.y, size.x, size.y)) {}

    ~Quad()
    {
        clear();
    }

    bool insert(const sf::Vector2f &point);

    void query(const AABB &range, bool mark = true);

    void render(sf::RenderWindow &window);

    static int count;

private:
    AABB boundary;
    QtNode node;

    std::array<Quad *, 4> children;

    void clear();
};

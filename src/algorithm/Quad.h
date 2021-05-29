#pragma once

#include "AABB.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include <iostream>
#include <memory>
#include <array>
#include <list>
#include <queue>

enum
{
    capacity = 2
};

// The quad class is a 4-ary tree, which represents the subdivisons of 2D space.
// Each quad stores the point which it contains.
class Quad
{
private:
    AABB boundary;

    std::array<sf::Vector2f, capacity> points;
    int index = 0;

    std::unique_ptr<Quad> ne;
    std::unique_ptr<Quad> nw;
    std::unique_ptr<Quad> se;
    std::unique_ptr<Quad> sw;

    bool divided = false;

public:
    Quad(const AABB &boundary = AABB(0, 0, 0, 0)) : boundary(boundary) {}

    Quad(const sf::Vector2f &center, const sf::Vector2f &size) : boundary(center.x, center.y, size.x, size.y) {}

    // subdivide quad into 4 smaller quads
    void subdivide();

    // inserts an element into tree at specified (x,y) position
    bool insert(sf::Vector2f point);

    // Returns the list of elements in quad tree that
    // are within the specified range
    std::list<sf::Vector2f> query(const AABB &range);

    void render(sf::RenderWindow &window);
};

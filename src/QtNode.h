#pragma once

#include "Point.h"
#include "AABB.h"

#include <SFML/Graphics/RenderWindow.hpp>

static const int qt_node_capacity = 2;

class QtNode
{
private:
    int size;
    Point *points[qt_node_capacity];

public:
    QtNode();
    ~QtNode();

    bool full() const;
    void insert(const sf::Vector2f &point);
    void query(const AABB &range, bool mark);
    void render(sf::RenderWindow &window);
};
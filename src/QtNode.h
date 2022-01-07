#pragma once

#include "Point.h"
#include "AABB.h"

#include <SFML/Graphics/RenderWindow.hpp>

class QtNode
{
public:
    QtNode();
    ~QtNode();

    bool full() const;
    bool empty() const;
    bool contains(const sf::Vector2f &point) const;
    void insert(const sf::Vector2f &point);
    void remove(const sf::Vector2f &point);
    void query(const AABB &range, bool mark);
    void render(sf::RenderWindow &window);

    static const int qt_node_capacity = 4;

private:
    int size_;
    Point *points_[qt_node_capacity];
};
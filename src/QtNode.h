#pragma once

#include "Point.h"

#include <array>

#include <SFML/Graphics.hpp>

static const int qt_node_capacity = 2;

class QtNode
{
private:
    int size;

    Point *points[qt_node_capacity];

public:
    QtNode() : size(0)
    {
        for (int i = 0; i < qt_node_capacity; i++)
        {
            points[i] = nullptr;
        }
    }

    ~QtNode()
    {
        for (int i = 0; i < qt_node_capacity; i++)
        {
            delete points[i];
        }
    }

    bool full() const
    {
        return size >= qt_node_capacity;
    }

    void insert(const sf::Vector2f &point)
    {
        points[size++] = new Point(point);
    }

    void query(const AABB &range, bool mark)
    {
        for (int i = 0; i < size; i++)
        {
            if (range.contains(points[i]->position()))
            {
                if (mark)
                {
                    points[i]->mark();
                }
                else
                {
                    points[i]->unmark();
                }
            }
        }
    }

    void render(sf::RenderWindow &window)
    {
        for (int i = 0; i < size; i++)
        {
            points[i]->render(window);
        }
    }
};
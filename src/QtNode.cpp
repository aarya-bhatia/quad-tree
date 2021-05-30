#include "QtNode.h"

QtNode::QtNode() : size(0)
{
    for (int i = 0; i < qt_node_capacity; i++)
    {
        points[i] = nullptr;
    }
}

QtNode::~QtNode()
{
    for (int i = 0; i < qt_node_capacity; i++)
    {
        delete points[i];
    }
}

bool QtNode::full() const
{
    return size >= qt_node_capacity;
}

void QtNode::insert(const sf::Vector2f &point)
{
    points[size++] = new Point(point);
}

void QtNode::query(const AABB &range, bool mark)
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

void QtNode::render(sf::RenderWindow &window)
{
    for (int i = 0; i < size; i++)
    {
        points[i]->render(window);
    }
}
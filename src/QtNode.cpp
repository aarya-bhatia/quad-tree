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
        points[i] = nullptr;
    }
}

bool QtNode::full() const
{
    return size >= qt_node_capacity;
}

bool QtNode::empty() const 
{
    return size == 0;
}

void QtNode::insert(const sf::Vector2f &point)
{
    if(full())
    {
        return;
    }

    for(int i = 0; i < qt_node_capacity; i++)
    {
        if(!points[i])
        {
            points[size] = new Point(point);
            size++;
            break;
        }
    }
}

void QtNode::remove(const sf::Vector2f &point)
{
    if(empty())
    {
        return;
    }

    for(int i = 0; i < qt_node_capacity; i++)
    {
        if(points[i] && points[i]->position() == point)
        {
            delete points[i];
            points[i] = nullptr;
            size--;
            break;
        }
    }
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

bool QtNode::contains(const sf::Vector2f &point) const
{
    for(int i = 0; i < size; i++)
    {
        if(points[i]->position() == point)
        {
            return true;
        }
    }

    return false;
}
#include "QtNode.h"

QtNode::QtNode() : size_(0)
{
    for (int i = 0; i < qt_node_capacity; i++)
    {
        points_[i] = nullptr;
    }
}

QtNode::~QtNode()
{
    for (int i = 0; i < qt_node_capacity; i++)
    {
        delete points_[i];
        points_[i] = nullptr;
    }
}

bool QtNode::full() const
{
    return size_ >= qt_node_capacity;
}

bool QtNode::empty() const 
{
    return size_ == 0;
}

void QtNode::insert(const sf::Vector2f &point)
{
    if(full())
    {
        return;
    }

    for(int i = 0; i < qt_node_capacity; i++)
    {
        if(!points_[i])
        {
            points_[size_] = new Point(point);
            size_++;
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
        if(points_[i] && points_[i]->position() == point)
        {
            delete points_[i];
            points_[i] = nullptr;
            size_--;
            break;
        }
    }
}

void QtNode::query(const AABB &range, bool mark)
{
    for (int i = 0; i < size_; i++)
    {
        if (range.contains(points_[i]->position()))
        {
            if (mark)
            {
                points_[i]->mark();
            }
            else
            {
                points_[i]->unmark();
            }
        }
    }
}

void QtNode::render(sf::RenderWindow &window)
{
    for (int i = 0; i < size_; i++)
    {
        points_[i]->render(window);
    }
}

bool QtNode::contains(const sf::Vector2f &point) const
{
    for(int i = 0; i < size_; i++)
    {
        if(points_[i]->position() == point)
        {
            return true;
        }
    }

    return false;
}
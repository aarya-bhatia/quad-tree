#include "Quad.h"

bool Quad::showPoints = true;
bool Quad::showGrid = true;

Quad::Quad(const AABB &boundary, int depth) : boundary_(boundary), depth_(depth)
{
    for (int i = 0; i < 4; i++)
    {
        children_[i] = nullptr;
    }
}

Quad::~Quad()
{
    clear();
}

Quad *Quad::createQtree(const sf::RenderWindow &window)
{
    return new Quad(AABB(0, 0, window.getSize().x, window.getSize().y));
}

bool Quad::insert(const sf::Vector2f &point)
{
    // At max capacity
    if(boundary_.getWidth() <= 1 || boundary_.getHeight() <= 1)
    {
        return false;
    }

    // Point does not belong in this region
    if (!boundary_.contains(point))
    {
        return false;
    }

    if (!node_.full())
    {
        node_.insert(point);
        return true;
    }

    if (boundary_.isNorthwest(point))
    {
        if (children_[northwest] == nullptr)
        {
            children_[northwest] = new Quad(boundary_.northwest(), depth_ + 1);
        }

        return children_[northwest]->insert(point);
    }
    else if (boundary_.isNortheast(point))
    {
        if (children_[northeast] == nullptr)
        {
            children_[northeast] = new Quad(boundary_.northeast(), depth_ + 1);
        }

        return children_[northeast]->insert(point);
    }
    else if (boundary_.isSouthwest(point))
    {
        if (children_[southwest] == nullptr)
        {
            children_[southwest] = new Quad(boundary_.southwest(), depth_ + 1);
        }

        return children_[southwest]->insert(point);
    }
    else if (boundary_.isSoutheast(point))
    {
        if (children_[southeast] == nullptr)
        {
            children_[southeast] = new Quad(boundary_.southeast(), depth_ + 1);
        }

        return children_[southeast]->insert(point);
    }

    return false;
}

void Quad::query(const Range &range)
{
    if (!boundary_.intersects(range.getBoundary()))
    {
        return;
    }

    node_.query(range.getBoundary(), range.isMarked());

    for(int i = 0; i < 4; i++)
    {
        if(children_[i])
        {
            children_[i]->query(range);
        }
    }
}

void Quad::render(sf::RenderWindow &window)
{
    if(Quad::showGrid)
    {
        boundary_.render(window);
    }

    if (Quad::showPoints)
    {
        node_.render(window);
    }

    for(int i = 0; i < 4; i++)
    {
        if(children_[i])
        {
            children_[i]->render(window);
        }
    }
}

void Quad::clear()
{
    for(int i = 0; i < 4; i++)
    {
        if (children_[i])
        {
            children_[i]->clear();
            delete children_[i];
            children_[i] = nullptr;
        }
    }
}

bool Quad::contains(const sf::Vector2f &point) const
{
    if(node_.contains(point))
    {
        return true;
    }

    for(int i = 0; i < 4; i++)
    {
        if(children_[i])
        {
            if(children_[i]->contains(point))
            {
                return true;
            } 
        }
    }

    return false;
}
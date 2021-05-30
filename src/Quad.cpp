#include "Quad.h"

int Quad::count = 0;

bool Quad::insert(const sf::Vector2f &point)
{
    if (!boundary.contains(point))
    {
        return false;
    }

    if (!node.full())
    {
        node.insert(point);

        Quad::count++;

        return true;
    }

    if (boundary.isNW(point))
    {
        if (children[northwest] == nullptr)
        {
            children[northwest] = new Quad(boundary.northwest());
        }

        return children[northwest]->insert(point);
    }
    else if (boundary.isNE(point))
    {
        if (children[northeast] == nullptr)
        {
            children[northeast] = new Quad(boundary.northeast());
        }

        return children[northeast]->insert(point);
    }
    else if (boundary.isSW(point))
    {
        if (children[southwest] == nullptr)
        {
            children[southwest] = new Quad(boundary.southwest());
        }

        return children[southwest]->insert(point);
    }
    else if (boundary.isSE(point))
    {
        if (children[southeast] == nullptr)
        {
            children[southeast] = new Quad(boundary.southeast());
        }

        return children[southeast]->insert(point);
    }

    return false;
}

void Quad::query(const AABB &range, bool mark)
{
    if (!boundary.intersects(range))
    {
        return;
    }

    node.query(range, mark);

    for (Quad *child : children)
    {
        if (child != nullptr)
        {
            child->query(range, mark);
        }
    }
}

void Quad::render(sf::RenderWindow &window)
{
    boundary.render(window);

    node.render(window);

    for (Quad *quad : children)
    {
        if (quad != nullptr)
        {
            quad->render(window);
        }
    }
}

void Quad::clear()
{
    for (Quad *child : children)
    {
        if (child != nullptr)
        {
            child->clear();
            delete child;
        }
    }
}
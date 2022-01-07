#include "Quad.h"

int Quad::count = 0;
bool Quad::showPoints = true;

Quad::Quad(const AABB &boundary) : boundary(boundary), node()
{
    for (int i = 0; i < 4; i++)
    {
        children[i] = nullptr;
    }
}

Quad::Quad(const sf::Vector2f &center, const sf::Vector2f &size)
{
    boundary = AABB(center.x, center.y, size.x, size.y);

    for (int i = 0; i < 4; i++)
    {
        children[i] = nullptr;
    }
}

Quad::~Quad()
{
    clear();
}

Quad *Quad::createQtree(const sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    return new Quad(sf::Vector2f(size.x / 2, size.y / 2), sf::Vector2f(size));
}

bool Quad::insert(const sf::Vector2f &point)
{
    if(Quad::count >= Quad::max_capacity)
    {
        return false;
    }

    if (!boundary.contains(point))
    {
        return false;
    }

    // Point already exists

    if(node.contains(point))
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

void Quad::query(const Range &range)
{
    if (!boundary.intersects(range.boundary))
    {
        return;
    }

    node.query(range.boundary, range.isMarked());

    for (Quad *child : children)
    {
        if (child != nullptr)
        {
            child->query(range);
        }
    }
}

void Quad::render(sf::RenderWindow &window)
{
    boundary.render(window);

    if (Quad::showPoints)
    {
        node.render(window);
    }

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
    for(int i = 0; i < 4; i++)
    {
        if (children[i])
        {
            children[i]->clear();
            delete children[i];
            children[i] = nullptr;
        }
    }
}

bool Quad::contains(const sf::Vector2f &point) const
{
    if(node.contains(point))
    {
        return true;
    }

    for(int i = 0; i < 4; i++)
    {
        if(children[i])
        {
            if(children[i]->contains(point))
            {
                return true;
            } 
        }
    }

    return false;
}
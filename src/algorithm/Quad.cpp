#include "Quad.h"

void Quad::subdivide()
{
    nw = std::make_unique<Quad>(boundary.northwest());
    ne = std::make_unique<Quad>(boundary.northeast());
    sw = std::make_unique<Quad>(boundary.southwest());
    se = std::make_unique<Quad>(boundary.southeast());

    divided = true;
}

bool Quad::insert(sf::Vector2f point)
{
    if (!boundary.contains(point))
    {
        return false;
    }

    if (index < capacity)
    {
        points[index++] = point;
        return true;
    }

    if (!divided)
    {
        subdivide();
    }

    return nw->insert(point) || ne->insert(point) || sw->insert(point) || se->insert(point);
}

std::list<sf::Vector2f> Quad::query(const AABB &range)
{
    std::list<sf::Vector2f> found;

    if (!boundary.intersects(range))
    {
        return found;
    }

    for (int i = 0; i < index; i++)
    {
        if (boundary.contains(points[i]))
        {
            found.push_back(points[i]);
        }
    }

    if (divided)
    {
        found.splice(found.end(), nw->query(range));
        found.splice(found.end(), ne->query(range));
        found.splice(found.end(), sw->query(range));
        found.splice(found.end(), se->query(range));
    }

    return found;
}

void Quad::render(sf::RenderWindow &window)
{
    boundary.render(window);

    if (divided)
    {
        nw->render(window);
        ne->render(window);
        sw->render(window);
        se->render(window);
    }
}
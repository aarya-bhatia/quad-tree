#pragma once

#include "AABB.h"
#include "QtNode.h"
#include "Range.h"

enum quadrants
{
    northeast,
    southeast,
    southwest,
    northwest
};

// The quad class is a 4-ary tree, which represents the subdivisons of 2D space.
class Quad
{
public:
    Quad(const AABB &boundary = AABB());
    Quad(const sf::Vector2f &center, const sf::Vector2f &size);
    ~Quad();

    bool contains(const sf::Vector2f &point) const;
    bool insert(const sf::Vector2f &point);
    void query(const Range &range);
    void render(sf::RenderWindow &window);

    static int count;
    static bool showPoints;
    static const int max_capacity = 10000;

    static Quad *createQtree(const sf::RenderWindow &window);

private:
    AABB boundary;
    QtNode node;
    Quad *children[4];

    void clear();
};

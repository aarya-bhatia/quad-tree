#pragma once

#include "AABB.h"
#include "QtNode.h"
#include "Range.h"

// The quad class is a 4-ary tree, which represents the subdivisons of 2D space.
class Quad
{
public:

    Quad(const AABB &boundary = AABB(), int depth = 0);

    ~Quad();

    bool contains(const sf::Vector2f &point) const;
    bool insert(const sf::Vector2f &point);
    void query(const Range &range);
    void render(sf::RenderWindow &window);

    int getDepth() const { return depth_; }

    static bool showPoints;
    static bool showGrid;

    static Quad *createQtree(const sf::RenderWindow &window);

private:
    AABB boundary_;
    QtNode node_;
    Quad *children_[4];
    int depth_;

    void clear();

    enum quadrants
    {
        northeast,
        southeast,
        southwest,
        northwest
    };

};

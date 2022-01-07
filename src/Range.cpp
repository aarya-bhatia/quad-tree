#include "Range.h"

Range::Range(float x, float y, float w, float h) : boundary_(x, y, w, h, sf::Color::Green)
{
    num_points_ = 0;
}

float Range::getWidth() const
{
    return boundary_.getWidth();
}

float Range::getHeight() const
{
    return boundary_.getHeight();
}

void Range::setWidth(float width)
{
    boundary_.setWidth(width);
}

void Range::setHeight(float height)
{
    boundary_.setHeight(height);
}

bool Range::isMarked() const
{
    return marked_;
}

void Range::setMarked(bool b)
{
    num_points_ = 0;
    marked_ = b;
}

void Range::render(sf::RenderWindow &window)
{
    boundary_.render(window);
}

void Range::setPosition(const sf::Vector2f &position)
{
    boundary_.setPosition(position);
}

const AABB &Range::getBoundary() const 
{
    return boundary_;
}
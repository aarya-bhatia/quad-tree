#include "Point.h"

const float Point::radius = 4;
const sf::Color Point::marked = sf::Color::Red;
const sf::Color Point::normal = sf::Color::White;

Point::Point(const sf::Vector2f &position)
{
    shape_ = sf::CircleShape(Point::radius);
    shape_.setFillColor(Point::normal);
    shape_.setPosition(position);
}

const sf::Vector2f &Point::position() const
{
    return shape_.getPosition();
}

void Point::mark()
{
    shape_.setFillColor(marked);
}

void Point::unmark()
{
    shape_.setFillColor(normal);
}

void Point::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}

std::ostream &operator<<(std::ostream &out, const sf::Vector2f &point)
{
    out << "(" << point.x << "," << point.y << ")";
    return out;
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
    out << point.position();
    return out;
}
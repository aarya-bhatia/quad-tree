#include "AABB.h"

/**
 * @brief Construct a new AABB object
 *
 * @param x Top-Left x-coord of region
 * @param y Top-Left y-coord of region
 * @param w width of region
 * @param h height of region
 * @param color color of outline of region
 */
AABB::AABB(float x, float y, float w, float h, const sf::Color &color)
{
    center_ = sf::Vector2f(x + w/2, y + h/2);
    radius_ = sf::Vector2f(w/2, h/2);
    color_ = color;
    shape_.setFillColor(sf::Color::Transparent);
    shape_.setOutlineThickness(2);
    shape_.setOutlineColor(color);
    shape_.setSize(sf::Vector2f(w, h));
    shape_.setPosition(x, y);
}

AABB::AABB(const sf::Vector2f &center, const sf::Vector2f &radius, const sf::Color &color): AABB(center.x, center.y, radius.x, radius.y, color)
{
}

float AABB::getWidth() const
{
    return radius_.x * 2;
}

float AABB::getHeight() const
{
    return radius_.y * 2;
}

float AABB::getHalfWidth() const 
{
    return radius_.x;
}

float AABB::getHalfHeight() const 
{
    return radius_.y;
}

const sf::Vector2f &AABB::getCenter() const
{
    return center_;
}

void AABB::setWidth(float width)
{
    if (width <= 0)
    {
        return;
    } 

    sf::Vector2f start = center_ - radius_;
    radius_.x = width/2;
    center_ = start + radius_;
    shape_.setSize(sf::Vector2f(getWidth(), getHeight()));
}

void AABB::setHeight(float height)
{
    if(height <= 0)
    {
        return;
    }

    sf::Vector2f start = center_ - radius_;
    radius_.y = height/2;
    center_ = start + radius_;
    shape_.setSize(sf::Vector2f(getWidth(), getHeight()));
}

void AABB::setPosition(const sf::Vector2f &position)
{
    center_.x = position.x + radius_.x;
    center_.y = position.y + radius_.y;
    shape_.setPosition(position);
}

///
// checks whether this box contains the given point
///
bool AABB::contains(const sf::Vector2f &point) const
{
    return point.x >= center_.x - radius_.x &&
           point.y >= center_.y - radius_.y &&
           point.x <= center_.x + radius_.x &&
           point.y <= center_.y + radius_.y;
}

bool AABB::contains(float x, float y) const
{
    return contains(sf::Vector2f(x, y));
}

///
// checks whether the other box intersects with this box.
// It cannot intersect if the left edge of other box is ahead of the right edge of this box.
// It cannot intersect if the right edge of other box is behind the left edge of this box.
// It cannot intersect if the bottom edge of other box is above the top edge of this box.
// It cannot intersect if the top edge of other box is below the bottom edge of this box.
// If any of these conditions are true, we return false.
///
bool AABB::intersects(const AABB &other) const
{
    return !(other.center_.x - other.radius_.x > center_.x + radius_.x ||
             other.center_.x + other.radius_.x < center_.x - radius_.x ||
             other.center_.y + other.radius_.y < center_.y - radius_.y ||
             other.center_.y - other.radius_.y > center_.y + radius_.y);
}

/*

x x x x x x x x
x . . x x . . x
x . . x x . . x
x x x x x x x x
x . . x x . . x
x . . x x . . x
x . . x x . . x
x x x x x x x x
 
*/

// returns the top right quad of this region
AABB AABB::northeast() const
{
    return AABB(center_.x, center_.y - radius_.y, radius_.x, radius_.y);
}

// returns the top left quad of this region
AABB AABB::northwest() const
{
    return AABB(center_.x - radius_.x, center_.y - radius_.y, radius_.x, radius_.y);
}

// returns the bottom left quad of this region
AABB AABB::southwest() const
{
    return AABB(center_.x - radius_.x, center_.y, radius_.x, radius_.y);
}

// returns the bottom right quad of this region
AABB AABB::southeast() const
{
    return AABB(center_.x, center_.y, radius_.x, radius_.y);
}

// checks if the point lies in the NE quadrant of box
bool AABB::isNortheast(const sf::Vector2f &point) const
{
    return point.x >= center_.x && point.y <= center_.y;
}

// checks if the point lies in the NW quadrant of box
bool AABB::isNorthwest(const sf::Vector2f &point) const
{
    return point.x <= center_.x && point.y <= center_.y;
}

// checks if the point lies in the SE quadrant of box
bool AABB::isSoutheast(const sf::Vector2f &point) const
{
    return point.x >= center_.x && point.y >= center_.y;
}

// checks if the point lies in the SW quadrant of box
bool AABB::isSouthwest(const sf::Vector2f &point) const
{
    return point.x <= center_.x && point.y >= center_.y;
}

void AABB::render(sf::RenderWindow &window)
{
    window.draw(shape_);
}

bool AABB::operator==(const AABB &other) const
{
    return center_ == other.center_ && radius_ == other.radius_;
}

float AABB::getX() const 
{
    return center_.x - radius_.x;
}

float AABB::getY() const
{
    return center_.y - radius_.y;
}

std::ostream &operator<<(std::ostream &out, const AABB &aabb)
{
    out << "AABB(" << aabb.getX() << ", " << aabb.getY() << ", " << aabb.getWidth() << ", " << aabb.getHeight() << ")";

    return out;
}
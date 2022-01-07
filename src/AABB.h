#pragma once

/**
 * Axis aligned bounding box
 */

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

class AABB
{
public:
    /**
     * @brief Construct a new AABB object
     *
     * @param x Top-Left x-coord of region
     * @param y Top-Left y-coord of region
     * @param w width of region
     * @param h height of region
     * @param color color of outline of region
     */
    AABB(float x = 0, float y = 0, float w = 0, float h = 0, const sf::Color &color = sf::Color::White);
    AABB(const sf::Vector2f &center, const sf::Vector2f &radius, const sf::Color &color = sf::Color::White);

    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getHalfWidth() const;
    float getHalfHeight() const;

    const sf::Vector2f &getCenter() const;

    void setWidth(float);
    void setHeight(float);
    void setPosition(const sf::Vector2f &position);

    ///
    // checks whether this box contains the given point
    ///
    bool contains(const sf::Vector2f &point) const;

    bool contains(float x, float y) const;

    ///
    // checks whether the other box intersects with this box.
    // It cannot intersect if the left edge of other box is ahead of the right edge of this box.
    // It cannot intersect if the right edge of other box is behind the left edge of this box.
    // It cannot intersect if the bottom edge of other box is above the top edge of this box.
    // It cannot intersect if the top edge of other box is below the bottom edge of this box.
    // If any of these conditions are true, we return false.
    ///
    bool intersects(const AABB &other) const;

    // returns the top right quad of this region
    AABB northeast() const;

    // returns the top left quad of this region
    AABB northwest() const;

    // returns the bottom left quad of this region
    AABB southwest() const;

    // returns the bottom right quad of this region
    AABB southeast() const;

    // checks if the point lies in the NE quadrant of box
    bool isNortheast(const sf::Vector2f &point) const;

    // checks if the point lies in the NW quadrant of box
    bool isNorthwest(const sf::Vector2f &point) const;

    // checks if the point lies in the SE quadrant of box
    bool isSoutheast(const sf::Vector2f &point) const;

    // checks if the point lies in the SW quadrant of box
    bool isSouthwest(const sf::Vector2f &point) const;

    void render(sf::RenderWindow &window);

    bool operator==(const AABB &other) const;

private:
    sf::Vector2f center_; // Center of region
    sf::Vector2f radius_; // Half dimension
    sf::RectangleShape shape_; // Rectangular boundary
    sf::Color color_; // Color of boundary
};

std::ostream &operator<<(std::ostream &out, const AABB &aabb);
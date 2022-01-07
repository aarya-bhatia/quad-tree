#pragma once

#include "AABB.h"

class Range
{
public:
    Range(float x, float y, float w, float h);

    float getWidth() const;
    float getHeight() const;
    void setWidth(float width);
    void setHeight(float height);
    bool isMarked() const;
    void setMarked(bool b);
    void render(sf::RenderWindow &window);
    void setPosition(const sf::Vector2f &position);
    const AABB &getBoundary() const; 

private:
    AABB boundary_;
    int num_points_;
    bool marked_ = false;
};
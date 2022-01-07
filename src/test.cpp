#include "acutest.hpp"
#include "cs225/HSLAPixel.h"
#include "Quad.h"
#include "AABB.h"
#include "Range.h"
#include <iostream>

void testHSLAPixel()
{
    cs225::HSLAPixel p;
    std::cout << p << std::endl;
}

void testAABB()
{
    AABB region(0, 0, 100, 100);

    std::cout << "Original: " << region << std::endl;
    std::cout << "NW: " << region.northwest() << std::endl;
    std::cout << "NE: " << region.northeast() << std::endl;
    std::cout << "SW: " << region.southwest() << std::endl;
    std::cout << "SE: " << region.southeast() << std::endl;

    TEST_CHECK(region.getX() == 0);
    TEST_CHECK(region.getY() == 0);
    TEST_CHECK(region.getCenter() == sf::Vector2f(50, 50));
    TEST_CHECK(region.getWidth() == 100);
    TEST_CHECK(region.getHeight() == 100);
    TEST_CHECK(region.intersects(region));
    TEST_CHECK(region.contains(50, 50));
    TEST_CHECK(!region.contains(200, 200));
    TEST_CHECK(region.isNortheast(sf::Vector2f(100, 0)));
    TEST_CHECK(region.isNorthwest(sf::Vector2f(0, 0)));
    TEST_CHECK(region.isSoutheast(sf::Vector2f(100, 100)));
    TEST_CHECK(region.isSouthwest(sf::Vector2f(0,100)));
    TEST_CHECK(region.northeast().contains(100, 0));
    TEST_CHECK(region.northwest().contains(0, 0));
    TEST_CHECK(region.southeast().contains(100, 100));
    TEST_CHECK(region.southwest().contains(0, 100));

    TEST_CHECK(region.northwest() == AABB(0, 0, 50, 50));
    TEST_CHECK(region.northeast() == AABB(50, 0, 50, 50));
    TEST_CHECK(region.southwest() == AABB(0, 50, 50, 50));
    TEST_CHECK(region.southeast() == AABB(50, 50, 50, 50));

    region.setPosition(sf::Vector2f(50, 50));
    TEST_CHECK(region.getCenter() == sf::Vector2f(100, 100));
    TEST_CHECK(region.contains(150, 150));

    region.setPosition(sf::Vector2f(0, 0));
    region.setWidth(50);
    region.setHeight(50);
    TEST_CHECK(region.getCenter() == sf::Vector2f(25, 25));
}

void testQuad()
{
    Quad *qtree = new Quad(AABB(0, 0, 100, 100));
    sf::Vector2f p(20, 20);
    TEST_CHECK(qtree->insert(p));
    TEST_CHECK(qtree->count == 1);
    TEST_CHECK(qtree->contains(p));
    delete qtree;
}

TEST_LIST = {
    {"testHSLAPixel", testHSLAPixel},
    {"testAABB", testAABB},
    {"testQuad", testQuad},
    {nullptr, nullptr}};
#include "../lib/acutest.hpp"
#include "Quad.h"
#include "AABB.h"
#include "Range.h"

void testAABB()
{
    AABB region(100, 100, 100, 100);
    TEST_CHECK(region.getHeight() == 200);
    TEST_CHECK(region.getWidth() == 200);
    TEST_CHECK(region.intersects(region));
    TEST_CHECK(region.contains(50, 50));
    TEST_CHECK(region.contains(200, 200));
    TEST_CHECK(!region.contains(250, 200));
}

void testQuad()
{
    Quad *qtree = new Quad(AABB(100, 100, 100, 100));

    sf::Vector2f p(20, 20);

    TEST_CHECK(qtree->insert(p));
    TEST_CHECK(qtree->count == 1);
    TEST_CHECK(qtree->contains(p));

    delete qtree;
}

TEST_LIST = 
{
    {"testAABB", testAABB},
    {"testQuad", testQuad},
    {nullptr, nullptr}
};
#include <gtest/gtest.h>
#include "Event/Event.h"

/**
 * @brief Test to ensure that a Event object can be instantiated.
 */
TEST(EventTest, itLives)
{
    Event event("Init", QDateTime::currentDateTime());
}

/**
 * @brief Test to verify that the method generates a valid event.
 */
TEST(EventTest, generateEventShouldReturnCorrectValue)
{
    Event event = Event::generateEvent("Init");

    EXPECT_FALSE(event.getEventType().isEmpty());
    EXPECT_TRUE(event.getTime() > QDateTime::currentDateTime());
}

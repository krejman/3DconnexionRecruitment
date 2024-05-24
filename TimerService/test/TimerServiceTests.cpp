#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ControlledClock.hpp"

class SimpleMock
{
public:
	MOCK_METHOD(void, callback1, ());
	MOCK_METHOD(void, callback2, ());
};

TEST(TimerServiceTest, ControlledClockTest_singleTick)
{
	ControlledClock clock;
	SimpleMock mock;
	clock.start();
	clock.setCallback([&mock]() { mock.callback1(); });
	EXPECT_CALL(mock, callback1());
	clock.increment();
}

TEST(TimerServiceTest, ControlledClockTest_multipleTicks)
{
	ControlledClock clock;
	SimpleMock mock;
	clock.start();
	clock.setCallback([&mock]() { mock.callback1(); });
	EXPECT_CALL(mock, callback1()).Times(5);
	clock.increment(5);
}
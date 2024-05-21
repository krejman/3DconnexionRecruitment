#include <gtest/gtest.h>
#include "ControlledClock.hpp"
#include <gmock/gmock.h>

class SimpleMock
{
public:
	MOCK_METHOD(void, call, ());
};

class ClockMock : public Clock
{

};

TEST(TimerServiceTest, ControlledClockTest_singleTick)
{
	ControlledClock clock;
	SimpleMock mock;
	clock.start();
	clock.setCallback([&mock]() { mock.call(); });
	EXPECT_CALL(mock, call());
	clock.increment();
}

TEST(TimerServiceTest, ControlledClockTest_multipleTicks)
{
	ControlledClock clock;
	SimpleMock mock;
	clock.start();
	clock.setCallback([&mock]() { mock.call(); });
	EXPECT_CALL(mock, call()).Times(5);
	clock.increment(5);
}
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ControlledClock.hpp"
#include "TimerService.hpp"

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

TEST(TimerServiceTest, TimerServiceTest_singleTimer)
{
	TimerService timerService;
	SimpleMock mock;
	auto timer = std::make_shared<Timer>(1, [&mock]() {mock.callback1(); });
	timerService.registerNewTimer(timer);
	EXPECT_CALL(mock, callback1());
	timerService.secondHasPassed();
}

TEST(TimerServiceTest, TimerServiceTest_multipleTimers)
{
	TimerService timerService;
	SimpleMock mock;
	auto timer1 = std::make_shared<Timer>(1, [&mock]() {mock.callback1(); });
	auto timer2 = std::make_shared<Timer>(3, [&mock]() {mock.callback2(); });
	timerService.registerNewTimer(timer1);
	timerService.registerNewTimer(timer2);
	EXPECT_CALL(mock, callback1());
	timerService.secondHasPassed();
	timerService.secondHasPassed();
	EXPECT_CALL(mock, callback2());
	timerService.secondHasPassed();
}

TEST(TimerServiceTest, TimerServiceTest_testCallback)
{
	TimerService timerService;
	SimpleMock mock;
	auto timer = std::make_shared<Timer>(1, [&mock]() {mock.callback1(); });
	timerService.registerNewTimer(timer);
	timerService.setCallback([&mock]() {mock.callback2(); });
	EXPECT_CALL(mock, callback1());
	EXPECT_CALL(mock, callback2());
	timerService.secondHasPassed();
}

TEST(TimerServiceTest, IntegrationTest)
{
	TimerService timerService;
	SimpleMock mock;
	ControlledClock clock;
	auto timer1 = std::make_shared<Timer>(2, [&mock]() {mock.callback1(); });
	auto timer2 = std::make_shared<Timer>(6, [&mock]() {mock.callback1(); });
	timerService.registerNewTimer(timer1);
	timerService.registerNewTimer(timer2);
	timerService.setCallback([&mock]() {mock.callback2(); });
	clock.setCallback([&timerService]() {timerService.secondHasPassed(); });
	clock.start();
	clock.increment();
	EXPECT_CALL(mock, callback1());
	EXPECT_CALL(mock, callback2());
	clock.increment();
	clock.increment(3);
	clock.stop();
	clock.increment();
	clock.increment(5);
	clock.start();
	EXPECT_CALL(mock, callback1());
	EXPECT_CALL(mock, callback2());
	clock.increment(2);
}
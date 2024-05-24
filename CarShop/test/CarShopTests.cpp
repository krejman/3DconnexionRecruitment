#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "CarData.hpp"
#include "TimerService.hpp"

using ::testing::SaveArg;

class TimerServiceMock : public TimerService
{
public:
	MOCK_METHOD(void, registerNewTimer, (std::shared_ptr<Timer>), (override));
	MOCK_METHOD(void, releaseTimer, (std::shared_ptr<Timer>), (override));
};

TEST(CarShopTest, CarData_creation)
{
	TimerServiceMock timerServiceMock;
	EXPECT_CALL(timerServiceMock, registerNewTimer);
	CarData carData(2000, 2000, "model", timerServiceMock);
}

TEST(CarShopTest, CarData_sell)
{
	TimerServiceMock timerServiceMock;
	EXPECT_CALL(timerServiceMock, registerNewTimer);
	CarData carData(2000, 2000, "model", timerServiceMock);
	EXPECT_CALL(timerServiceMock, releaseTimer);
	carData.sell();
}

TEST(CarShopTest, CarData_fireTimer)
{
	TimerServiceMock timerServiceMock;
	std::shared_ptr<Timer> timer;
	EXPECT_CALL(timerServiceMock, registerNewTimer).WillOnce(SaveArg<0>(&timer));
	CarData carData(2000, 2000, "model", timerServiceMock);
	EXPECT_CALL(timerServiceMock, registerNewTimer);
	timer->fire();
}

TEST(CarShopTest, CarData_timersDuration)
{
	TimerServiceMock timerServiceMock;
	std::shared_ptr<Timer> timer1, timer2;
	int longTimerDuration{ 30 }, shortTimerDuration{ 10 };
	EXPECT_CALL(timerServiceMock, registerNewTimer).WillOnce(SaveArg<0>(&timer1));
	CarData carData(2000, 2000, "model", timerServiceMock);
	EXPECT_EQ(timer1->getSeconds(), longTimerDuration);
	EXPECT_CALL(timerServiceMock, registerNewTimer).WillOnce(SaveArg<0>(&timer2));
	timer1->fire();
	EXPECT_EQ(timer2->getSeconds(), shortTimerDuration);
}
#include <chrono>
#include "RealClock.hpp"

RealClock::RealClock() : thread(&RealClock::run, this) { }

void RealClock::run()
{
	while (not endClock.load())
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (running.load() and callback)
			callback();
	}
}
void RealClock::start()
{
	running.store(true);
}
void RealClock::stop()
{
	running.store(false);
}
void RealClock::end()
{
	endClock.store(true);
	thread.join();
}
void RealClock::setCallback(std::function<void()> _callback)
{
	callback = _callback;
}
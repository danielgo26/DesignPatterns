#pragma once
#include <iostream>
#include <thread>
#include <chrono>

#include "Observer.h"
	
class ProgressReporter : public Observer
{
protected:
	std::ostream& displayProgressStream;

	//path
	std::string currOperatingFilePath = "";

	//bytes
	long long totalBytesToRead = 0;
	long long bytesProcessedByLastTick = 0;
	long long totalBytesProcessedByFar = 0;

	//speed
	double currAverageSpeed = -1;

	//time
	std::chrono::steady_clock::time_point currStartTime;
	bool noStartTime = true;
	long long elapsed_time = 0;
	long long currTimeRemaining = -1;

	long long getTimeRemaining();
	void showProgressBar(long long timeElapsed, long long timeRemaining, std::ostream& os = std::cout) const;
public:
	ProgressReporter(size_t bytesToRead, std::ostream& displayProgressStream = std::cout);

	long long getTotalBytesToReadCount()const;
	void setTotalBytesToReadCount(size_t bytesToRead);
	void update(const Context& context) override;
};
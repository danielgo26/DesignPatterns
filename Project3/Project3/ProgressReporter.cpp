#include <iomanip>
#include <fstream>

#include "ProgressReporter.h"

ProgressReporter::ProgressReporter(size_t bytesToRead, std::ostream& displayProgressStream)
	:totalBytesToRead(bytesToRead), displayProgressStream(displayProgressStream) {}

long long ProgressReporter::getTimeRemaining()
{
	long long timeRemaining = 0;
	//enters only when we have set a start time interval
	if (!this->noStartTime)
	{
		std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

		long long elapsed_miliseconds =
			(std::chrono::duration_cast<std::chrono::milliseconds>(end_time - this->currStartTime).count());
		this->elapsed_time += elapsed_miliseconds;

		if (elapsed_miliseconds == 0)
		{
			elapsed_miliseconds = 1;
		}

		//bytes per milisecond
		double currSpeed = (this->bytesProcessedByLastTick / (double)elapsed_miliseconds);
		if (currSpeed == 0)
		{
			currSpeed = 1;
		}
		//no speed estimated by far
		if (this->currAverageSpeed == -1)
		{
			this->currAverageSpeed = currSpeed;
		}
		else//get average
		{
			this->currAverageSpeed = (this->currAverageSpeed + currSpeed) / 2.0;
		}
		if (this->currAverageSpeed == 0)
		{
			this->currAverageSpeed = 1;
		}

		//get time remainining
		timeRemaining = (this->totalBytesToRead - this->totalBytesProcessedByFar) / this->currAverageSpeed;

		this->noStartTime = true;
	}

	//reset timer and bytes read by last tick
	if (this->noStartTime)//the timer should be reset
	{
		this->currStartTime = std::chrono::steady_clock::now();
		this->noStartTime = false;
	}
	if (timeRemaining < 0)
	{
		timeRemaining = 0;
	}
	return timeRemaining;
}

void ProgressReporter::showProgressBar(long long timeElapsed, long long timeRemaining, std::ostream& os) const
{
	const size_t progressBarWidth = 50;
	size_t totalTime = timeElapsed + timeRemaining;
	size_t elapsedProgress = 0;
	if (this->totalBytesToRead == 0)
	{
		elapsedProgress = 50;
	}
	else
		elapsedProgress = (timeElapsed * progressBarWidth) / totalTime;
	if (elapsedProgress > 50)
	{
		elapsedProgress = 50;
	}
	int remainingProgress = progressBarWidth - elapsedProgress;

	os << "[";

	for (size_t i = 0; i < elapsedProgress; ++i) {
		os << "/";
	}

	for (size_t i = 0; i < remainingProgress; ++i) {
		os << ".";
	}

	if (totalTime == 0)
	{
		os << "] " << std::fixed << std::setprecision(3) << 100 << "%\r";
	}
	else
	{
		double percentageRemaining = (static_cast<double>(timeElapsed) / totalTime) * 100;
		if (percentageRemaining > 100)
			percentageRemaining = 100;

		os << "] " << std::fixed << std::setprecision(3) << percentageRemaining << "%\r";
	}

	os.flush();
}

long long ProgressReporter::getTotalBytesToReadCount()const
{
	return this->totalBytesToRead;
}

void ProgressReporter::setTotalBytesToReadCount(size_t bytesToRead)
{
	this->totalBytesToRead = bytesToRead;
}

void ProgressReporter::update(const Context& context)
{
	if (context.operationType == type::startReadingNewByteGroup)
	{
		getTimeRemaining();
		this->currTimeRemaining = -1;
		system("cls");
		showProgressBar(this->totalBytesProcessedByFar,
			this->totalBytesToRead - this->totalBytesProcessedByFar, this->displayProgressStream);
		this->displayProgressStream << std::endl;

		this->displayProgressStream << "Proccessing: " << this->currOperatingFilePath << "...";
	}
	else if (context.operationType == type::endReadingNewByteGroup)
	{
		this->bytesProcessedByLastTick = context.bytesProcessed;
		this->totalBytesProcessedByFar += this->bytesProcessedByLastTick;
		this->currTimeRemaining = getTimeRemaining();

		system("cls");
		showProgressBar(this->totalBytesProcessedByFar,
			this->totalBytesToRead - this->totalBytesProcessedByFar, this->displayProgressStream);
		this->displayProgressStream << std::endl;
		this->displayProgressStream << "Proccessing: " << this->currOperatingFilePath << "...";
		this->displayProgressStream << "  " << context.bytesProcessed << " bytes processed so far";
		this->displayProgressStream << "( " << currTimeRemaining << " ms remaining...)" << std::endl;

		//if we want to simulate any delay, uncomment this:
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	else if (context.operationType == type::getFileInfo)
	{
		this->currTimeRemaining = -1;
		this->currOperatingFilePath = context.fileName;
	}
	else if (context.operationType == type::resetInitialState)
	{
		//path
		this->currOperatingFilePath = "";

		//bytes
		this->bytesProcessedByLastTick = 0;
		this->totalBytesProcessedByFar = 0;

		//speed
		this->currAverageSpeed = -1;

		//time
		this->noStartTime = true;
		this->elapsed_time = 0;
		this->currTimeRemaining = -1;
	}
	else
	{
		system("cls");
		this->displayProgressStream << "Unknown message...";
	}
}
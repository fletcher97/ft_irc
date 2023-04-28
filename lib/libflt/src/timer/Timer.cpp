#include <iostream>
#include <sstream>

#include "Timer.hpp"
#include "Log.hpp"

flt::Timer::Timer(std::string name)
{
	this->_name = name;
	clock_gettime(CLOCK_REALTIME, &this->_start);
}


flt::Timer::~Timer()
{
	this->log();
}


void
flt::Timer::log() const
{
	LOG_INFO("Clock " << this->_name << " ran for " << this->get_elapsed() << " second")
}	// Timer::log


std::string
flt::Timer::get_elapsed() const
{
	timespec now;
	std::ostringstream converter;


	clock_gettime(CLOCK_REALTIME, &now);
	double elapsed = static_cast< double >(now.tv_sec - this->_start.tv_sec)
		+ static_cast< double >(now.tv_nsec - this->_start.tv_nsec) / 1000000000;

	converter.precision(9);
	converter << std::fixed << elapsed;

	return converter.str();
}	// Timer::get_elapsed


void
flt::Timer::reset()
{
	clock_gettime(CLOCK_REALTIME, &this->_start);
}	// Timer::reset

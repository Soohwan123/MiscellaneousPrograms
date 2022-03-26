/*	Jd.cpp

	Date and time library to_string method implementations.

=============================================================

Version 2021.09.26
	Updated: for C++ 20

=============================================================

Copyright Soohwan Kim

The copyright to the computer program(s) herein
is the property of Soohwan Kim, Canada.
The program(s) may be used and/or copied only with
the written permission of Soohwan Kim
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/

#include <khronos.hpp>
#include <khronos/Julian_day.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <sstream>
#include <ctime>
#include <cassert>
#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>


// Jd default constructor. Initialize to the current local time.
namespace khronos{
	khronos::Jd::Jd() : jd_(0) {
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		Jd const now(WTIMEOFDAY);
		Jd const today(NOTIMEOFDAY);
		jd_ = gregorian_to_jd(
			year_t(tmNow.tm_year) + 1900,
			month_t(tmNow.tm_mon) + 1,
			day_t(tmNow.tm_mday),
			hour_t(tmNow.tm_hour),
			minute_t(tmNow.tm_min),
			second_t(tmNow.tm_sec)
		);

	}
	namespace detail {
		jd_t jd_to_jdn_real(jd_t day) {
			return floor(day + 0.5);
		}
	}

	jd_t jd_to_jdn(jd_t day) {
		assert(day >= -31738.5 && "Minimum convertable date not provided.");
		return khronos::detail::jd_to_jdn_real(day);
	}


	/** Print the Jd Day as a string. */
	std::string khronos::Jd::to_string() const {
		std::ostringstream oss;
		oss << "JD " << jd_;
		return oss.str();
	}
}


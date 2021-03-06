#pragma once

/*
khronos\timeofday.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'time-of-day' declarations.
*/

#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cmath>

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/utility.hpp>

namespace khronos {
	constexpr second_t SECONDS_PER_DAY = 86400;
	constexpr second_t VULCAN_SECONDS_PER_DAY = 52488;


	// OPERATORS
	// ====================
	/**	time_am */
	constexpr tod_t operator ""_am(unsigned long long time) {
		if (time < 12 && time != 12) {
			return static_cast<tod_t>(time);
		}
		else if (time == 12) {
			return static_cast<tod_t>(0);
		}
	}
	/**	time_pm */
	constexpr tod_t operator ""_pm(unsigned long long time) {
		if (time < 12 && time != 12 && time != 0) {
			return static_cast<tod_t>(time + 12);
		}
		else if (time == 12) {
			return static_cast<tod_t>(12);
		}
	}

	/*!	Provides tod of jd .
	\return jdn of tod.
	\param hour [in]  hour of time [1..24]
	\param minute [in] minute of time [0..59]
	\param second [in] second of time [0..60]
	*/

	constexpr jd_t tod(hour_t hour, minute_t minute, second_t second) {
		return static_cast<jd_t>((second + (60 * static_cast<jd_t>(hour * 60 + minute))) / SECONDS_PER_DAY);
	}

	/*!	Provides tod of jd from vulcan jdn .
	\return jdn of tod.
	\param hour [in]  hour of time [1..24]
	\param minute [in] minute of time [0..59]
	\param second [in] second of time [0..60]
	*/
	constexpr jd_t vulcanTod(hour_t hour, minute_t minute, second_t second) {
		return static_cast<jd_t>((second + (54 * static_cast<jd_t>(hour * 54 + minute))) / VULCAN_SECONDS_PER_DAY);
	}

	/*!	Provides tod of jd .
	\return real hour minute second.
	\param hour [in]  jdn
	*/
	inline jd_t tod(jd_t jd) { return static_cast<jd_t>((jd + 0.5) - floor(jd + 0.5)); }

	/*!	Provides tod of jd from vulcan jdn.
	\return real hour minute second.
	\param hour [in]  jdn
	*/
	inline jd_t vulcanTod(jd_t jd) { return static_cast<jd_t>((jd + 0.6) - floor(jd + 0.6)); }


	class TimeOfDay {
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;
	public:
		TimeOfDay();
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }
		
		TimeOfDay(hour_t hour, minute_t minute, second_t second) : hour_(hour), minute_(minute), second_(second) {}
		TimeOfDay(jd_t jd) : hour_(static_cast<hour_t>(floor(jd*24))) , minute_(static_cast<minute_t>(floor(((jd*24)- floor(jd * 24)) * 60))), second_(static_cast<second_t>(floor((((((jd * 24) - floor(jd * 24)) * 60)-floor(((jd * 24) - floor(jd * 24)) * 60)) * 60) + 0.5))) {}
	};
	
	

	class VulcanTimeOfDay {
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;
	public:
		VulcanTimeOfDay();
		constexpr hour_t hour() const { return hour_; }
		constexpr minute_t minute() const { return minute_; }
		constexpr second_t second() const { return second_; }

		VulcanTimeOfDay(hour_t hour, minute_t minute, second_t second) : hour_(hour), minute_(minute), second_(second) {}
		VulcanTimeOfDay(jd_t jd) : hour_(static_cast<hour_t>(floor(jd * 15))), minute_(static_cast<minute_t>(floor(((jd * 15) - floor(jd * 15)) * 45))), second_(static_cast<second_t>(floor((((((jd * 15) - floor(jd * 15)) * 45) - floor(((jd * 15) - floor(jd * 15)) * 45)) * 45) + 0.6))) {}
	};

}

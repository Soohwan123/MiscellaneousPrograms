/**	@file Julian.cpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar class implementation.
	*/

#include <khronos/julian_calendar.hpp>
#include <cassert>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/timeofday.hpp>
#include <khronos/utility.hpp>

namespace khronos {
	/**	Julian default constructor.  Initialize to the current local time. */
	Julian::Julian() {
		time_t nowTime = time(NULL);
		struct tm tmNow;
		localtime_s(&tmNow, &nowTime);
		year_ = year_t(tmNow.tm_year) + 1900;
		month_ = month_t(tmNow.tm_mon) + 1;
		day_ = day_t(tmNow.tm_mday);
		hour_ = hour_t(tmNow.tm_hour);
		minute_ = minute_t(tmNow.tm_min);
		second_ = second_t(tmNow.tm_sec);
	}


	/** Print the Julian Date as a string. */
	std::string khronos::Julian::to_string() const {
		std::ostringstream oss;
		oss << civil::day_name(civil::day_of_week(to_jd())) << ", ";
		oss << julian_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		if (year_ <= 0)
			oss << (-year_ + 1) << " BC, ";
		else
			oss << year_ << " AD, ";
		if (hour_ > 12)
			oss << (hour_ - 12) << ":";
		else if (hour_ == 24)
			oss << 00 << ":";
		else oss << hour_ << ":";

		if (minute_ < 10)
			oss << "0" << minute_ << ":";
		else
			oss << minute_ << ":";
		if (second_ < 10)
			oss << "0" << second_;
		else
			oss << second_;
		if (hour_ > 12 || (hour_ == 12 && minute_ > 0) || (hour_ == 12 && second_ > 0))
			oss << " pm";
		else
			oss << " am";

		return oss.str();
	}


	/** Julian + (integer year) operator. */
	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_year_integer const& year) {
		khronos::year_t y = dt.year() + year.nYears_;
		khronos::month_t m = dt.month();
		khronos::day_t d = dt.day();
		khronos::hour_t h = dt.hour();
		khronos::minute_t min = dt.minute();
		khronos::second_t s = dt.second();
		if (m == khronos::February && d == 29 && !khronos::is_julian_leapyear(y))
			d = 28;
		return khronos::Julian::Julian(y, m, d, h, min, s);
	}


	/** Julian + (integer month) operator. */
	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_month_integer const& month) {
		khronos::year_t yearsToAdd = month.nMonths_ / 12;
		khronos::month_t monthsToAdd = month.nMonths_ % 12;
		khronos::year_t y = dt.year() + yearsToAdd;
		khronos::month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= khronos::month_t(adjustment * 12);
		khronos::day_t d = std::min(dt.day(), khronos::julian_days_in_month(m, khronos::is_julian_leapyear(y)));
		khronos::hour_t h = dt.hour();
		khronos::minute_t min = dt.minute();
		khronos::second_t s = dt.second();
		return khronos::Julian::Julian(y, m, d, h, min, s);
	}


	/* Julian + (day) operator */

	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_day const& day) {


		jd_t dayN = static_cast<jd_t>(day.nDays_);
		jd_t sum = dayN + julian_to_jd(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(sum, y, m, d, h, mi, s);
		return khronos::Julian::Julian(y, m, d, h, mi, s);
	}


	/* Julian + (hour) operator */

	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_hour const& hour) {

		jd_t temp = tod(dt.hour()+ hour.nHours_, dt.minute(), dt.second());

		jd_t sum = julian_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(temp).hour(), TimeOfDay(temp).minute(), TimeOfDay(temp).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(sum, y, m, d, h, mi, s);
		return khronos::Julian::Julian(y, m, d, h, mi, s);

	}


	/* Julian + (minute) operator */


	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_minute const& minute) {
		jd_t tempSum = tod(dt.hour(), dt.minute()+ minute.nMinutes_, dt.second());

		jd_t sum = julian_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(tempSum).hour(), TimeOfDay(tempSum).minute(), TimeOfDay(tempSum).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(sum, y, m, d, h, mi, s);

		return khronos::Julian::Julian(y, m, d, h, mi, s);

	}

	/* Julian + (second) operator */


	khronos::Julian operator + (khronos::Julian const& dt, khronos::detail::packaged_second const& second) {

		jd_t tempSum = tod(dt.hour(), dt.minute()+ second.nSeconds_, dt.second());

		jd_t sum = julian_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(tempSum).hour(), TimeOfDay(tempSum).minute(), TimeOfDay(tempSum).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_julian(sum, y, m, d, h, mi, s);

		return khronos::Julian::Julian(y, m, d, h, mi, s);

		return khronos::Julian::Julian(y, m, d, h, mi, s);
	}
};
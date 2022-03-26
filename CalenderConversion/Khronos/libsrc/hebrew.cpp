/**	@file Hebrew.cpp
	@author Garth Santor
	@date 2013-10-20

	Hebrew calendar class implementation.
	*/

#include <khronos/hebrew_calendar.hpp>
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
	/**	Hebrew default constructor.  Initialize to the current local time. */
	Hebrew::Hebrew() {
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


	/** Print the Hebrew Date as a string. */
	std::string khronos::Hebrew::to_string() const {
		std::ostringstream oss;
		oss << hebrew_month_name(month_) << ' ' << (unsigned)day_ << ' ';
		oss << year_ << ", ";
		if (hour_ > 12)
			oss << (hour_ - 12) << ":";
		else if (hour_ == 24 || hour_ == 0)
			oss << 12 << ":";
		else oss << hour_ << ":";

		if (minute_ < 10)
			oss << "0" << minute_ << ":";
		else
			oss << minute_ << ":";
		if (second_ < 10)
			oss << "0" << second_;
		else
			oss << second_;
		if (hour_ > 12 || (hour_ == 12 && minute_ >= 0) || (hour_ == 12 && second_ >= 0))
			oss << " pm";
		else if (hour_ == 24)
			oss << " am";
		else
			oss << " am";

		return oss.str();
	}


	/** Hebrew + (integer year) operator. */
	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_year_integer const& year) {
		khronos::year_t y = dt.year() + year.nYears_;
		khronos::month_t m = dt.month();
		khronos::day_t d = dt.day();
		khronos::hour_t h = dt.hour();
		khronos::minute_t min = dt.minute();
		khronos::second_t s = dt.second();
		if (m == khronos::February && d == 29 && !khronos::is_hebrew_leapyear(y))
			d = 28;
		return khronos::Hebrew::Hebrew(y, m, d, h, min, s);
	}


	/** Hebrew + (integer month) operator. */
	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_month_integer const& month) {
		khronos::year_t yearsToAdd = month.nMonths_ / 12;
		khronos::month_t monthsToAdd = month.nMonths_ % 12;
		khronos::year_t y = dt.year() + yearsToAdd;
		khronos::month_t m = dt.month() + monthsToAdd;

		int adjustment = (m - 1) / 12 + (m - 12) / 12;
		y += adjustment;
		m -= khronos::month_t(adjustment * 12);
		khronos::day_t d = std::min(dt.day(), khronos::hebrew_days_in_month(m, khronos::is_hebrew_leapyear(y)));
		khronos::hour_t h = dt.hour();
		khronos::minute_t min = dt.minute();
		khronos::second_t s = dt.second();
		return khronos::Hebrew::Hebrew(y, m, d, h, min, s);
	}


	/* Hebrew + (day) operator */

	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_day const& day) {


		jd_t dayN = static_cast<jd_t>(day.nDays_);
		jd_t sum = dayN + hebrew_to_jd(dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(sum, y, m, d, h, mi, s);
		return khronos::Hebrew::Hebrew(y, m, d, h, mi, s);
	}


	/* Hebrew + (hour) operator */

	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_hour const& hour) {

		jd_t tempSum = tod(dt.hour() + hour.nHours_, dt.minute(), dt.second());

		jd_t sum = hebrew_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(tempSum).hour(), TimeOfDay(tempSum).minute(), TimeOfDay(tempSum).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(sum, y, m, d, h, mi, s);
		return khronos::Hebrew::Hebrew(y, m, d, h, mi, s);

	}


	/* Hebrew + (minute) operator */


	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_minute const& minute) {
		jd_t tempSum = tod(dt.hour(), dt.minute() + minute.nMinutes_, dt.second());

		jd_t sum = hebrew_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(tempSum).hour(), TimeOfDay(tempSum).minute(), TimeOfDay(tempSum).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(sum, y, m, d, h, mi, s);

		return khronos::Hebrew::Hebrew(y, m, d, h, mi, s);

	}

	/* Hebrew + (second) operator */


	khronos::Hebrew operator + (khronos::Hebrew const& dt, khronos::detail::packaged_second const& second) {

		jd_t tempSum = tod(dt.hour(), dt.minute(), dt.second() + second.nSeconds_);

		jd_t sum = hebrew_to_jd(dt.year(), dt.month(), dt.day(), TimeOfDay(tempSum).hour(), TimeOfDay(tempSum).minute(), TimeOfDay(tempSum).second());
		year_t y;
		month_t m;
		day_t d;
		hour_t h;
		minute_t mi;
		second_t s;
		jd_to_hebrew(sum, y, m, d, h, mi, s);

		return khronos::Hebrew::Hebrew(y, m, d, h, mi, s);

	}
};
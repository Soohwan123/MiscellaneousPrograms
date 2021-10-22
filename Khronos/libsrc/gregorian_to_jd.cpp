/*
khronos\gregorian_to_jdn.cpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'gregorian::to_jdn' implementation.
*/


#include <khronos.hpp>
#include <khronos/gregorian_calendar.hpp>
#include <cassert>


/**	Real-number implementation. */
namespace khronos {
	namespace detail {

		jd_t greg2jd_real(year_t year, month_t month, day_t dayOfMonth, hour_t hour, minute_t minute, second_t second) {
			long long y = year - 1;
			return
				GREGORIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				- floor(y / 100.0)
				+ floor(y / 400.0)
				+ floor(((367.0 * month - 362.0) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_gregorian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth
				+ tod(hour, minute, second);
		}

		jd_t greg2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			long long y = year - 1;
			return
				GREGORIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				- floor(y / 100.0)
				+ floor(y / 400.0)
				+ floor(((367.0 * month - 362.0) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_gregorian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth;
		}

		/*	Integer implementation (wikipedia) */
		constexpr jd_t greg2jd_integer(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return tod(hour, minute, second) + day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
		}

		constexpr jd_t greg2jd_integer(year_t year, month_t month, day_t day) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045 - 0.5;
		}
	}
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");
		assert(hour >= 0 && "Minimum hour is 0");
		assert(hour <= 23 && "Maximum hour is 23");
		assert(minute >= 0 && "Minimum minute is 0");
		assert(minute <= 59 && "Maximum minute is 59");
		assert(second >= 0 && "Minimum second is 0");
		assert(second <= 59 && "Maximum second is 59");

		assert(greg2jd_integer(year, month, day, hour, minute, second) == detail::greg2jd_real(year, month, day, hour, minute, second));
		return khronos::detail::greg2jd_integer(year, month, day, hour, minute, second);
	}
	jd_t gregorian_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");

		assert(greg2jd_integer(year, month, day) == detail::greg2jd_real(year, month, day));
		return khronos::detail::greg2jd_integer(year, month, day);
	}
}
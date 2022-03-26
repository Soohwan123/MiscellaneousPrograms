/**	@file Islamic_to_jd.cpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar conversion implementations.
	*/

#include <khronos/islamic_calendar.hpp>
#include <khronos.hpp>
#include <cassert>
#include <algorithm>


	/**	Real-number implementation. */
namespace khronos {
	namespace detail {

		jd_t islamic2jd_real(year_t year, month_t month, day_t dayOfMonth, hour_t hour, minute_t minute, second_t second) {
			long long y = year - 1;
			jd_t temp;
			if (tod(hour, minute, second) >= 0.5) {
				temp = tod(hour, minute, second) - 1;
			}
			else {
				temp = tod(hour, minute, second);
			}
			return
				dayOfMonth
				+ floor(29.5 * (month - 1))
				+ ((year - 1) * 354)
				+ floor((3 + 11 * year) / 30)
				+ ISLAMIC_EPOCH - 1
				+ temp;
		}

		jd_t islamic2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			return
				dayOfMonth
				+ floor(29.5 * (month - 1))
				+ ((year - 1) * 354)
				+ floor((3 + 11 * year) / 30)
				+ ISLAMIC_EPOCH - 1;
		}


		/*!	Convert a islamic Day Number to the Proleptic islamic Calendar
			\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
			\param month [in] 1..12
			\param day [in] 1..31
		*/
		inline void jd_to_islamic_real(jd_t jd, year_t& year, month_t& month, day_t& day) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			int monthImp = floor((jd - (29 + islamic2jd_real(year, 1, 1))) / 29.5) + 1.0;
			jd = floor(jd) + 0.5;
			year = floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631);
			month = std::min(12, monthImp);
			day = jd - islamic2jd_real(year, month, 1) + 1;

		}

		inline void jd_to_islamic_real(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			hour = TimeOfDay(tod(jd)).hour();
			minute = TimeOfDay(tod(jd)).minute();
			second = TimeOfDay(tod(jd)).second();
			int monthImp = floor((jd - (29 + islamic2jd_real(year, 1, 1))) / 29.5) + 1;
			jd = floor(jd) + 0.5;
			year = floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631);
			month = std::min(12, monthImp);
			day = jd - islamic2jd_real(year, month, 1) + 1;
			
		}


	};
	jd_t islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 30");
		assert(hour >= 0 && "Minimum hour is 0");
		assert(hour <= 23 && "Maximum hour is 23");
		assert(minute >= 0 && "Minimum minute is 0");
		assert(minute <= 59 && "Maximum minute is 59");
		assert(second >= 0 && "Minimum second is 0");
		assert(second <= 59 && "Maximum second is 59");

		return khronos::detail::islamic2jd_real(year, month, day, hour, minute, second);
	}
	jd_t islamic_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");


		return khronos::detail::islamic2jd_real(year, month, day);
	}

	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");
		using namespace utility;
		int monthImp = floor((jd - (29 + detail::islamic2jd_real(year, 1, 1))) / 29.5) + 1.0;
		jd = floor(jd) + 0.5;
		year = floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631);
		month = std::min(12, monthImp);
		day = jd - detail::islamic2jd_real(year, month, 1) + 1;

#if defined( _DEBUG )
		{
			year_t y;
			month_t m;
			day_t d;
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_islamic_real(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
	}
	void jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");
		using namespace utility;
		hour = TimeOfDay(tod(jd)).hour();
		minute = TimeOfDay(tod(jd)).minute();
		second = TimeOfDay(tod(jd)).second();
		int monthImp = floor((jd - (29 + detail::islamic2jd_real(year, 1, 1))) / 29.5) + 1;
		jd = floor(jd) + 0.5;
		year = floor((30 * (jd - ISLAMIC_EPOCH) + 10646) / 10631);
		month = std::min(12, monthImp);
		day = jd - detail::islamic2jd_real(year, month, 1) + 1;
	}
#if defined( _DEBUG )
	{
		second_t s;
		minute_t min;
		hour_t h;
		year_t y;
		month_t m;
		day_t d;
		assert(year == y);
		assert(month == m);
		assert(day == d);
		detail::jd_to_islamic_real(jd, y, m, d);
		assert(year == y);
		assert(month == m);
		assert(day == d);
	}
#endif
}


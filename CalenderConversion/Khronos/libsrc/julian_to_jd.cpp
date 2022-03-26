/**	@file Julian_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Date and time library Julian conversion implementations.
	*/

#include <khronos/julian_calendar.hpp>
#include <khronos.hpp>
#include <cassert>


	/**	Real-number implementation. */
namespace khronos {
	namespace detail {

		jd_t julian2jd_real(year_t year, month_t month, day_t dayOfMonth, hour_t hour, minute_t minute, second_t second) {
			long long y = year - 1;
			return
				JULIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				+ floor(((367.0 * month - 362.0) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_julian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth
				+ tod(hour, minute, second);
		}

		jd_t julian2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			long long y = year - 1;
			return
				JULIAN_EPOCH - 1
				+ 365 * y
				+ floor(y / 4.0)
				+ floor(((367.0 * month - 362.0) / 12.0)
					+ ((month <= 2)
						? 0
						: (is_julian_leapyear(year) ? -1 : -2)))
				+ dayOfMonth;
		}

		/*	Integer implementation (wikipedia) */
		constexpr jd_t julian2jd_integer(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return tod(hour, minute, second) + day + (153 * m + 2) / 5 + 365 * y + y / 4- 32083 - 0.5;
		}

		constexpr jd_t julian2jd_integer(year_t year, month_t month, day_t day) {
			long long a = (14 - month) / 12;
			long long y = year + 4800 - a;
			long long m = month + 12 * a - 3;
			return day + (153 * m + 2) / 5 + 365 * y + y / 4 - 32083 - 0.5;
		}


		/*!	Convert a Julian Day Number to the Proleptic Julian Calendar
			\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
			\param month [in] 1..12
			\param day [in] 1..31
		*/
		void jd_to_julian_real(jd_t jd, year_t& year, month_t& month, day_t& day) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;

			double wjd, depoch, quadricent, dqc, cent;
			wjd = floor(jd + 0.5);
			depoch = wjd + 1524;
			quadricent = floor((depoch -122.1) / 365.25);
			dqc = floor(quadricent*365.25);
			cent = floor((depoch-dqc)/30.6001);
			if (cent < 14) {
				month = static_cast<month_t>(floor(cent - 1));
			}
			else {
				month = static_cast<month_t>(floor(cent - 13));
			}
			
			if (month > 2) {
				year = static_cast<year_t>(floor(quadricent - 4716));
			}
			else {
				year = static_cast<year_t>(floor(quadricent - 4715));
			}
			day = static_cast<day_t>(depoch - dqc - floor(30.6001 * cent));
		}

		void jd_to_julian_real(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			double wjd, depoch, quadricent, dqc, cent;
			wjd = floor(jd + 0.5);
			depoch = wjd + 1524;
			quadricent = floor((depoch - 122.1) / 365.25);
			dqc = floor(quadricent * 365.25);
			cent = floor((depoch - dqc) / 30.6001);
			if (cent < 14) {
				month = static_cast<month_t>(floor(cent - 1));
			}
			else {
				month = static_cast<month_t>(floor(cent - 13));
			}

			if (month > 2) {
				year = static_cast<year_t>(floor(quadricent - 4716));
			}
			else {
				year = static_cast<year_t>(floor(quadricent - 4715));
			}
			day = static_cast<day_t>(depoch - dqc - floor(30.6001 * cent));
			/*double wjd, depoch, quadricent, dqc, cent;
			wjd = floor(jd + 0.5);
			depoch = wjd + 1524;
			quadricent = floor((depoch - 122.1) / 365.25);
			dqc = floor(quadricent * 365.25);
			cent = floor((depoch - dqc) / 30.6001);
			if (cent < 14) {
				month = static_cast<month_t>(floor(cent - 1));
			}
			else if (cent > 14) {
				month = static_cast<month_t>(floor(cent - 13));
			}

			if (month > 2) {
				year = static_cast<year_t>(floor(quadricent - 4716));
			}
			else {
				year = static_cast<year_t>(floor(quadricent - 4715));
			}
			day = static_cast<day_t>(depoch - dqc - floor(30.6001 * cent));*/
			hour = TimeOfDay(tod(jd)).hour();
			minute = TimeOfDay(tod(jd)).minute();
			second = TimeOfDay(tod(jd)).second();
		}

		// integer implementation
		inline void jd_to_julian_integer(jd_t jd, year_t& year, month_t& month, day_t& day) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			jd = floor(jd + 0.5);
			long long j = static_cast<long long>(jd + 1524);
			long long g = floor((j - 122.1) / 365.25);
			long long dg = floor(g * 365.25);
			long long c = floor((j - dg) / 30.6001);
			if (c < 14) {
				month = static_cast<month_t>(floor(c - 1));
			}
			else {
				month = static_cast<month_t>(floor(c - 13));
			}

			if (month > 2) {
				year = static_cast<year_t>(floor(g - 4716));
			}
			else {
				year = static_cast<year_t>(floor(g - 4715));
			}
			day = static_cast<day_t>(j - dg - floor(30.6001 * c));
		}

		// integer implementation
		inline void jd_to_julian_integer(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			hour = TimeOfDay(tod(jd)).hour();
			minute = TimeOfDay(tod(jd)).minute();
			second = TimeOfDay(tod(jd)).second();
			jd = floor(jd + 0.5);
			long long j = static_cast<long long>(jd + 1524);
			long long g = floor((j - 122.1) / 365.25);
			long long dg = floor(g * 365.25);
			long long c = floor((j - dg) / 30.6001);
			if (c < 14) {
				month = static_cast<month_t>(floor(c - 1));
			}
			else {
				month = static_cast<month_t>(floor(c - 13));
			}

			if (month > 2) {
				year = static_cast<year_t>(floor(g - 4716));
			}
			else {
				year = static_cast<year_t>(floor(g - 4715));
			}
			day = static_cast<day_t>(j - dg - floor(30.6001 * c));
			
		}
	};
	jd_t julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
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

		assert(julian2jd_integer(year, month, day, hour, minute, second) == detail::julian2jd_real(year, month, day, hour, minute, second));
		return khronos::detail::julian2jd_integer(year, month, day, hour, minute, second);
	}
	jd_t julian_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");

		assert(julian2jd_integer(year, month, day) == detail::julian2jd_real(year, month, day));
		return khronos::detail::julian2jd_integer(year, month, day);
	}
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");

		jd = floor(jd + 0.5);
		long long j = static_cast<long long>(jd + 1524);
		long long g = floor((j - 122.1) / 365.25);
		long long dg = floor(g * 365.25);
		long long c = floor((j - dg) / 30.6001);
		if (c < 14) {
			month = static_cast<month_t>(floor(c - 1));
		}
		else {
			month = static_cast<month_t>(floor(c - 13));
		}

		if (month > 2) {
			year = static_cast<year_t>(floor(g - 4716));
		}
		else {
			year = static_cast<year_t>(floor(g - 4715));
		}
		day = static_cast<day_t>(j - dg - floor(30.6001 * c));

#if defined( _DEBUG )
		{
			year_t y;
			month_t m;
			day_t d;
			detail::jd_to_julian_integer(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_julian_real(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
	}
	void jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");
		hour = TimeOfDay(tod(jd)).hour();
		minute = TimeOfDay(tod(jd)).minute();
		second = TimeOfDay(tod(jd)).second();

		jd = floor(jd + 0.5);
		long long j = static_cast<long long>(jd + 1524);
		long long g = floor((j - 122.1) / 365.25);
		long long dg = floor(g * 365.25);
		long long c = floor((j - dg) / 30.6001);
		if (c < 14) {
			month = static_cast<month_t>(floor(c - 1));
		}
		else{
			month = static_cast<month_t>(floor(c - 13));
		}

		if (month > 2) {
			year = static_cast<year_t>(floor(g - 4716));
		}
		else {
			year = static_cast<year_t>(floor(g - 4715));
		}
		day = static_cast<day_t>(j - dg - floor(30.6001 * c));
		
	}
#if defined( _DEBUG )
		{
			second_t s;
			minute_t min;
			hour_t h;
			year_t y;
			month_t m;
			day_t d;
			detail::jd_to_julian_integer(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_julian_real(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
}

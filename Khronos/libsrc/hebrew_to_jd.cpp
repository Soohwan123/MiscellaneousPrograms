/**	@file Hebrew_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Hebrew calendar conversion implementations.
	*/

#include <khronos/hebrew_calendar.hpp>
#include <khronos.hpp>
#include <cassert>


	/**	Real-number implementation. */
namespace khronos {
	namespace detail {

		jd_t hebr2jd_real(year_t year, month_t month, day_t dayOfMonth, hour_t hour, minute_t minute, second_t second) {
			
			jd_t temp = HEBREW_EPOCH + hebrew_delay_of_week(year) + hebrew_adjacent_year(year) + dayOfMonth + 1;
			long long monthTemp = 0;
			if (month < 7) {
				for (int i = 1; i < month - 1; i++) {
					monthTemp += hebrew_days_in_month(year, i);
				}
				temp = temp + monthTemp;
			}
			else {
				for (int i = 7; i < month - 1; i++) {
					monthTemp += hebrew_days_in_month(year, i);
				}
				temp = temp + monthTemp;
			}
			jd_t todTemp = tod(hour, minute, second);
			if (todTemp >= 0.5) {
				todTemp--;
			}
			temp = temp + todTemp;
			return temp;
		}

		jd_t hebr2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			jd_t temp = HEBREW_EPOCH + hebrew_delay_of_week(year) + hebrew_adjacent_year(year) + dayOfMonth + 1;
			long long monthTemp  = 0;
			if (month < 7) {
				for (int i = 1; i < month - 1; i++) {
					monthTemp += hebrew_days_in_month(year, i);
				}
				temp = temp + monthTemp;
			}
			else {
				for (int i = 7; i < month - 1; i++) {
					monthTemp += hebrew_days_in_month(year, i);
				}
				temp = temp + monthTemp;
			}
			return temp;
		}

		/*!	Convert a Julian Day Number to the Proleptic hebrew Calendar
			\param year [in] Astronomical year
			\param month [in] 1..13
			\param day [in] 1..30
		*/
		void jd_to_hebrew_real(jd_t jd, year_t& year, month_t& month, day_t& day) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			jd = floor(jd) + 0.5;
			int count = floor(((jd - HEBREW_EPOCH) * 98496) / 35975351);
			year = count - 1;
			int i = count;
			while (jd >= hebr2jd_real(i, 7, 1)) {
				year = year + 1;
				i++;
			}
			int first = 1;
			if (jd < hebr2jd_real(year, 1, 1)) {
				first = 7;
			}
			month = first;
			i = first;
			while (jd > hebr2jd_real(year, i, hebrew_days_in_month(year, i))) {
				month = month + 1;
				i++;
			}
			day = floor(jd - hebr2jd_real(year, month, 1) + 1);

		}
		/*!	Convert a Julian Day Number to the Proleptic hebrew Calendar
			\param year [in] Astronomical year
			\param month [in] 1..13
			\param day [in] 1..30
		*/
		void jd_to_hebrew_real(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			jd = floor(jd) + 0.5;
			int count = floor(((jd - HEBREW_EPOCH) * 98496) / 35975351);
			year = count - 1;
			int i = count;
			while (jd >= hebr2jd_real(i, 7, 1)) {
				year = year + 1;
				i++;
			}
			int first = 1;
			if (jd < hebr2jd_real(year, 1, 1)) {
				first = 7;
			}
			month = first;
			i = first;
			while (jd > hebr2jd_real(year, i, hebrew_days_in_month(year, i))) {
				month = month + 1;
				i++;
			}
			day = floor(jd - hebr2jd_real(year, month, 1) + 1);
			hour = TimeOfDay(tod(jd)).hour();
			minute = TimeOfDay(tod(jd)).minute();
			second = TimeOfDay(tod(jd)).second();
		}

	}
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
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

		return khronos::detail::hebr2jd_real(year, month, day, hour, minute, second);
	}
	jd_t hebrew_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");

		return khronos::detail::hebr2jd_real(year, month, day);
	}



	/*!	Convert a Julian Day Number to the Proleptic hebrew Calendar
			\param year [in] Astronomical year
			\param month [in] 1..13
			\param day [in] 1..30
		*/
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");

		jd = floor(jd - 0.5) + 0.5;
		jd = floor(jd) + 0.5;
		int count = floor(((jd - HEBREW_EPOCH) * 98496) / 35975351);
		year = count - 1;
		int i = count;
		while (jd >= detail::hebr2jd_real(i, 7, 1)) {
			year = year + 1;
			i++;
		}
		int first = 1;
		if (jd < detail::hebr2jd_real(year, 1, 1)) {
			first = 7;
		}
		month = first;
		i = first;
		while (jd > detail::hebr2jd_real(year, i, hebrew_days_in_month(year, i))) {
			month = month + 1;
			i++;
		}
		day = floor(jd - detail::hebr2jd_real(year, month, 1) + 1);

#if defined( _DEBUG )
		{
			year_t y;
			month_t m;
			day_t d;
			detail::jd_to_hebrew_integer(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_hebrew_real(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
	}
	/*!	Convert a Julian Day Number to the Proleptic hebrew Calendar
			\param year [in] Astronomical year
			\param month [in] 1..13
			\param day [in] 1..30
		*/
	void jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");

		using namespace utility;
		hour = TimeOfDay(tod(jd)).hour();
		minute = TimeOfDay(tod(jd)).minute();
		second = TimeOfDay(tod(jd)).second();
		jd = floor(jd) + 0.5;
		int count = floor(((jd - HEBREW_EPOCH) * 98496) / 35975351);
		year = count - 1;
		int i = count;
		while (jd >= detail::hebr2jd_real(i, 7, 1)) {
			year = year + 1;
			i++;
		}
		int first = 1;
		if (jd < detail::hebr2jd_real(year, 1, 1)) {
			first = 7;
		}
		month = first;
		i = first;
		while (jd > detail::hebr2jd_real(year, i, hebrew_days_in_month(year, i))) {
			month = month + 1;
			i++;
		}
		day = floor(jd - detail::hebr2jd_real(year, month, 1) + 1);
		




#if defined( _DEBUG )
		{
			second_t s;
			minute_t min;
			hour_t h;
			year_t y;
			month_t m;
			day_t d;
			detail::jd_to_hebrew_integer(jd, y, m, d, h, min, s);
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_hebrew_real(jd, y, m, d, h, min, s);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
	}
}
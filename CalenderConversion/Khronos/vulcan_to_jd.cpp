/**	@file vulcan_to_jd.cpp
	@author Garth Santor
	@date 2012-09-14

	Date and time library vulcan conversion implementations.
	*/

#include <khronos/vulcan_calendar.hpp>
#include <khronos.hpp>
#include <cassert>


	/**	Real-number implementation. */
namespace khronos {
	namespace detail {

		jd_t vulcan2jd_real(year_t year, month_t month, day_t dayOfMonth, hour_t hour, minute_t minute, second_t second) {
			long long y = year - 1;
			return
				VULCAN_EPOCH
				+ floor(266.4 * y)
				+ floor((21) * (month - 1))
				+ floor(dayOfMonth-1);
				+ vulcanTod(hour, minute, second);
		}

		jd_t vulcan2jd_real(year_t year, month_t month, day_t dayOfMonth) {
			long long y = year - 1;
			return
				VULCAN_EPOCH
				+ floor(266.4 * y)
				+ floor((21) * (month - 1))
				+ floor(dayOfMonth - 1);
		}


		/*!	Convert a vulcan Day Number to the Proleptic vulcan Calendar
			\param year [in] Astronomical year 
			\param month [in] 1..12
			\param day [in] 1..31
		*/
		void jd_to_vulcan_real(jd_t jd, year_t& year, month_t& month, day_t& day) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;

			double wjd = floor(jd - 0.6) + 0.6;
			double extEpoch = wjd - VULCAN_EPOCH;
			int y = (extEpoch / 266.4) + 1;

			double tempM = 0;
			if ((extEpoch / 266.4) >= 1) {
				if ((utility::mod(extEpoch, 266.4) < 21)) {
					tempM = 1;
				}
				else {
					double tempM = (utility::mod(extEpoch, 266.4) / 21) + 1;
				}
			}
			else if((extEpoch / 266.4) < 0){
				if ((utility::mod(extEpoch, -266.4) > -21)) {
					tempM = 1;
				}
				else {
					double tempM = (utility::mod(extEpoch, -266.4) / 21) - 1;
				}
			}
			else {
				if (extEpoch < 21) {
					tempM = 1 ;
				}
				else {
					tempM = (extEpoch / 21)+1;
				}
			}
			double tempD = (((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) - (int)(((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) + 1;
			if ((extEpoch / 266.4) >= 1) {
				if ((utility::mod(extEpoch, 266.4) < 21)) {
					tempD = utility::mod(extEpoch, 266.4)+1;
				}
				else {
					tempD = utility::mod(utility::mod(extEpoch, 266.4), 21) + 1;
				}
			}
			else if ((extEpoch / 266.4) < 0) {
				if ((utility::mod(extEpoch, -266.4) > -21)) {
					tempD = utility::mod(extEpoch, -266.4) - 1;
				}
				else {
					tempD = utility::mod(utility::mod(extEpoch, -266.4), 21) - 1;
				}
			}
			else {
				if (extEpoch < 21) {
					tempD = extEpoch+1;
				}
				else {
					tempD = utility::mod(extEpoch, 21)+1;
				}
			}
			if (y < 0) {
				year = y - 1;
			}
			else {
				year = y;
			}
			if (floor(tempM < 0)) {
				month = -floor(tempM);
			}
			else {
				month = floor(tempM);
			}

			if (floor(tempD < 0)) {
				day = -floor(tempD);
			}
			else {
				day = floor(tempD);
			}
		}

		void jd_to_vulcan_real(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
			assert(jd >= -31738.5 && "Minimum convertible date not provided.");
			using namespace utility;
			

			double wjd = floor(jd - 0.6) + 0.6;
			double extEpoch = wjd - VULCAN_EPOCH;
			int y = (extEpoch / 266.4) + 1;

			double tempM = 0;
			if ((extEpoch / 266.4) >= 1) {
				if ((utility::mod(extEpoch, 266.4) < 21)) {
					tempM = 1;
				}
				else {
					double tempM = (utility::mod(extEpoch, 266.4) / 21) + 1;
				}
			}
			else if ((extEpoch / 266.4) < 0) {
				if ((utility::mod(extEpoch, -266.4) > -21)) {
					tempM = 1;
				}
				else {
					double tempM = (utility::mod(extEpoch, -266.4) / 21) - 1;
				}
			}
			else {
				if (extEpoch < 21) {
					tempM = 1;
				}
				else {
					tempM = (extEpoch / 21) + 1;
				}
			}
			double tempD = (((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) - (int)(((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) + 1;
			if ((extEpoch / 266.4) >= 1) {
				if ((utility::mod(extEpoch, 266.4) < 21)) {
					tempD = utility::mod(extEpoch, 266.4) + 1;
				}
				else {
					tempD = utility::mod(utility::mod(extEpoch, 266.4), 21) + 1;
				}
			}
			else if ((extEpoch / 266.4) < 0) {
				if ((utility::mod(extEpoch, -266.4) > -21)) {
					tempD = utility::mod(extEpoch, -266.4) - 1;
				}
				else {
					tempD = utility::mod(utility::mod(extEpoch, -266.4), 21) - 1;
				}
			}
			else {
				if (extEpoch < 21) {
					tempD = extEpoch + 1;
				}
				else {
					tempD = utility::mod(extEpoch, 21) + 1;
				}
			}
			if (y < 0) {
				year = y - 1;
			}
			else {
				year = y;
			}
			if (floor(tempM < 0)) {
				month = -floor(tempM);
			}
			else {
				month = floor(tempM);
			}

			if (floor(tempD < 0)) {
				day = -floor(tempD);
			}
			else {
				day = floor(tempD);
			}
			hour = VulcanTimeOfDay(vulcanTod(jd)).hour();
			minute = VulcanTimeOfDay(vulcanTod(jd)).minute();
			second = VulcanTimeOfDay(vulcanTod(jd)).second();
			
		}

		
	};
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) {
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

		
		return khronos::detail::vulcan2jd_real(year, month, day, hour, minute, second);
	}
	jd_t vulcan_to_jd(year_t year, month_t month, day_t day) {
		assert(year > -4800 && "Minimum year is 4800 BCE");
		assert(month >= 1 && "Minimum month is January = 1");
		assert(month <= 12 && "Maximum month is December = 12");
		assert(day >= 1 && "Minimum day is 1");
		assert(day <= 31 && "Maximum day is 31");

		
		return khronos::detail::vulcan2jd_real(year, month, day);
	}
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");
		using namespace utility;
		double wjd = floor(jd - 0.6) + 0.6;
		double extEpoch = wjd - VULCAN_EPOCH;
		int y = (extEpoch / 266.4) + 1;

		double tempM = 0;
		if ((extEpoch / 266.4) >= 1) {
			if ((utility::mod(extEpoch, 266.4) < 21)) {
				tempM = 1;
			}
			else {
				double tempM = (utility::mod(extEpoch, 266.4) / 21) + 1;
			}
		}
		else if ((extEpoch / 266.4) < 0) {
			if ((utility::mod(extEpoch, -266.4) > -21)) {
				tempM = 1;
			}
			else {
				double tempM = (utility::mod(extEpoch, -266.4) / 21) - 1;
			}
		}
		else {
			if (extEpoch < 21) {
				tempM = 1;
			}
			else {
				tempM = (extEpoch / 21) + 1;
			}
		}
		double tempD = (((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) - (int)(((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) + 1;
		if ((extEpoch / 266.4) >= 1) {
			if ((utility::mod(extEpoch, 266.4) < 21)) {
				tempD = utility::mod(extEpoch, 266.4) + 1;
			}
			else {
				tempD = utility::mod(utility::mod(extEpoch, 266.4), 21) + 1;
			}
		}
		else if ((extEpoch / 266.4) < 0) {
			if ((utility::mod(extEpoch, -266.4) > -21)) {
				tempD = utility::mod(extEpoch, -266.4) - 1;
			}
			else {
				tempD = utility::mod(utility::mod(extEpoch, -266.4), 21) - 1;
			}
		}
		else {
			if (extEpoch < 21) {
				tempD = extEpoch + 1;
			}
			else {
				tempD = utility::mod(extEpoch, 21) + 1;
			}
		}
		if (y < 0) {
			year = y - 1;
		}
		else {
			year = y;
		}
		if (floor(tempM < 0)) {
			month = -floor(tempM);
		}
		else {
			month = floor(tempM);
		}

		if (floor(tempD < 0)) {
			day = -floor(tempD);
		}
		else {
			day = floor(tempD);
		}
#if defined( _DEBUG )
		{
			year_t y;
			month_t m;
			day_t d;
			detail::jd_to_vulcan_integer(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
			detail::jd_to_vulcan_real(jd, y, m, d);
			assert(year == y);
			assert(month == m);
			assert(day == d);
		}
#endif
	}
	void jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second) {
		assert(jd >= -31738.5 && "Minimum convertable date not provided.");
		using namespace utility;
		

		/*double wjd = floor(jd + 0.5);
		double extEpoch = wjd - VULCAN_EPOCH;
		int y = extEpoch / 266.4;
		double tempM = (utility::mod(extEpoch, 266.4) / 21);
		double tempD = utility::mod(utility::mod(extEpoch, 266.4), 21);
		year = y;
		month = floor(tempM);
		day = floor(tempD);
		hour = VulcanTimeOfDay(tod(jd)).hour();
		minute = VulcanTimeOfDay(tod(jd)).minute();
		second = VulcanTimeOfDay(tod(jd)).second();*/
		double wjd = floor(jd - 0.6) + 0.6;
		double extEpoch = wjd - VULCAN_EPOCH;
		int y = (extEpoch / 266.4) + 1;

		double tempM = 0;
		if ((extEpoch / 266.4) >= 1) {
			if ((utility::mod(extEpoch, 266.4) < 21)) {
				tempM = 1;
			}
			else {
				double tempM = (utility::mod(extEpoch, 266.4) / 21) + 1;
			}
		}
		else if ((extEpoch / 266.4) < 0) {
			if ((utility::mod(extEpoch, -266.4) > -21)) {
				tempM = 1;
			}
			else {
				double tempM = (utility::mod(extEpoch, -266.4) / 21) - 1;
			}
		}
		else {
			if (extEpoch < 21) {
				tempM = 1;
			}
			else {
				tempM = (extEpoch / 21) + 1;
			}
		}
		double tempD = (((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) - (int)(((extEpoch / 266.4) - (int)(extEpoch / 266.4)) / 21) + 1;
		if ((extEpoch / 266.4) >= 1) {
			if ((utility::mod(extEpoch, 266.4) < 21)) {
				tempD = utility::mod(extEpoch, 266.4) + 1;
			}
			else {
				tempD = utility::mod(utility::mod(extEpoch, 266.4), 21) + 1;
			}
		}
		else if ((extEpoch / 266.4) < 0) {
			if ((utility::mod(extEpoch, -266.4) > -21)) {
				tempD = utility::mod(extEpoch, -266.4) - 1;
			}
			else {
				tempD = utility::mod(utility::mod(extEpoch, -266.4), 21) - 1;
			}
		}
		else {
			if (extEpoch < 21) {
				tempD = extEpoch + 1;
			}
			else {
				tempD = utility::mod(extEpoch, 21) + 1;
			}
		}
		if (y < 0) {
			year = y - 1;
		}
		else {
			year = y;
		}
		if (floor(tempM < 0)) {
			month = -floor(tempM);
		}
		else {
			month = floor(tempM);
		}

		if (floor(tempD < 0)) {
			day = -floor(tempD);
		}
		else {
			day = floor(tempD);
		}
		hour = VulcanTimeOfDay(vulcanTod(jd)).hour();
		minute = VulcanTimeOfDay(vulcanTod(jd)).minute();
		second = VulcanTimeOfDay(vulcanTod(jd)).second();
	}
#if defined( _DEBUG )
	{
		second_t s;
		minute_t min;
		hour_t h;
		year_t y;
		month_t m;
		day_t d;
		detail::jd_to_vulcan_integer(jd, y, m, d);
		assert(year == y);
		assert(month == m);
		assert(day == d);
		detail::jd_to_vulcan_real(jd, y, m, d);
		assert(year == y);
		assert(month == m);
		assert(day == d);
	}
#endif
}
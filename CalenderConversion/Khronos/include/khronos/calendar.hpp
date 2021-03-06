#pragma once

/*
khronos\calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'civil' declarations.
*/


#include <khronos/def.hpp>
#include <khronos/utility.hpp>
#include <array>
#include <cassert>

namespace khronos {

	namespace civil {

		namespace detail {
			constexpr std::array<std::array<day_t, 13>, 2> daysInMonth = {
				0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
				0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31,
			};

	
		}


		/** Get the full name of the civil day of week.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = Monday
		*/
		constexpr char const* day_name(day_t day) {
			constexpr char const* names[7] = {
				"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}


		/**	Returns the number of days in the given month of the civil calendar.
			@return The number of days in the given month.
			@param month [in] month number [1..12]
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/
		constexpr day_t days_in_month(month_t month, bool isLeapYear) {
			return detail::daysInMonth[isLeapYear][month];
		}

		


		// month functions

		/** Get the full name of the civil month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"January", "February", "March", "April", "May", "June",
				"July", "August", "September", "October", "November", "December"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}

		inline day_t day_of_week(jd_t jd) { return static_cast<day_t>(khronos::utility::mod(jd + 0.5, 7)); }
		inline tod_t tod(jd_t jd) { return static_cast<tod_t>(jd + 0.5 - floor(jd + 0.5)); }
		/** Get the short name of the civil month.
			@return pointer to the 3-letter month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* month_name_short(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
				"JUL", "AUG", "SEP", "OCT", "NOV", "DEC"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}
	}

	namespace islamic {


		constexpr std::array<std::array<day_t, 13>, 2> IslamicDaysInMonth = {
			0, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29,
			0, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 30,
		};

		inline day_t islamic_day_of_week(jd_t jd) { return static_cast<day_t>(khronos::utility::mod(jd + 0.5, 7)); }

		/**	Returns the number of days in the given month of the Islamic calendar.
			@return The number of days in the given month.
			@param month [in] month number [1..12]
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/
		constexpr day_t islamic_days_in_month(month_t month, bool isLeapYear) {
			return islamic::IslamicDaysInMonth[isLeapYear][month];
		}


		/** Get the full name of the civil day of week.
			@return pointer to the day name as a c-string.
			@param day [in] day number [0..6], where 0 = al-'ahad
		*/
		constexpr char const* day_name(day_t day) {
			constexpr char const* names[7] = {
				"al-'ahad", "al-'ithnayn", "alth-thalatha", "al-'arb`a'", "as-sabt", "al-jum`a", "as-sabt"
			};
			assert(day >= 0);
			assert(day < 7);
			return names[day];
		}


		// month functions

		/** Get the full name of the islamic month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* islamic_month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"", "Muharram", "Safar", "Rabi'al-Awwal",
				"Rabi'ath-Thani", "Jumada I-Ula", "Jumada t-Tania", "Rajab", "Sha'ban", "Ramadan", "Shawwal",
				"Dhu I-Qa'da", "Dhu I-Hijja"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}


	}

	namespace hebrew {
		// month functions

		/** Get the full name of the hebrew month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..13]
		*/
		constexpr std::array<std::array<day_t, 14>, 3> HebrewDaysInMonth = {
			0, 30, 29, 30, 29, 30, 29, 30, 29, 29, 29, 30, 30, 29,
			0, 30, 29, 30, 29, 30, 29, 30, 29, 30, 29, 30, 30, 29,
			0, 30, 29, 30, 29, 30, 29, 30, 30, 30, 29, 30, 30, 29,	
		};
		constexpr std::array<month_t, 2> MonthsInYears = {
				13,14,
		};

		/**	Returns the number of days in the given month of the  hebrew calendar.
			@return The number of days in the given month.
			@param month [in] month number [1..13]
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/
		constexpr day_t hebrew_days_in_month(month_t month, bool isLeapYear) {
			return hebrew::HebrewDaysInMonth[isLeapYear][month];
		}

		/**	Returns the number of months in the given year of the  hebrew calendar.
			@return The number of days in the given month.
			@param isLeapYear [in] 'true' for leap year, 'false' otherwise.
			*/

		constexpr month_t hebrew_months_in_year(bool isLeapYear) {
			return hebrew::MonthsInYears[isLeapYear];
		}

		// month functions

		/** Get the full names of the hebrew month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..13]
		*/
		constexpr char const* hebrew_full_month_name_long(month_t month) {
			constexpr char const* const names[14] = {
				"",
				"Nisan", "Iyyar", "Sivan", "Tammuz",
				"Av", "Elul", "Tishri", "Heshvan",
				"Kislev", "Teveth", "Shevat", "Adar", "Veadar"
			};

			assert(month > 0);
			assert(month < 14);
			return names[month];
		}

		/** Get the month's names of the short years.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/
		constexpr char const* hebrew_short_month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"Nisan", "Iyyar", "Sivan", "Tammuz",
				"Av", "Elul", "Tishri", "Heshvan",
				"Kislev", "Teveth", "Shevat", "Veadar"
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}


	}

	namespace vulcan {

		// month functions

		/** Get the full name of the vulcan month.
			@return pointer to the month name as a c-string.
			@param month [in] month number [1..12]
		*/

		constexpr char const* vulcan_month_name_long(month_t month) {
			constexpr char const* const names[13] = {
				"",
				"Z'at",
				"D'ruh",
				"K'riBrax",
				"re'T'Khutai",
				"T'keKhuti",
				"Khuti",
				"Ta'Krat",
				"K'ri'lior",
				"et'khior",
				"T'lakht",
				"T'ke'Tas",
				"Tasmeen",
			};

			assert(month > 0);
			assert(month < 13);
			return names[month];
		}
	}



	// VALUES
	enum civil_month_codes_long { January = 1, February, March, April, May, June, July, August, September, October, November, December };
	enum civil_month_codes_short { JAN = January, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	enum civil_weekday_codes_long { Monday = 0, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };
	enum civil_weekday_codes_short { MON = Monday, TUE, WED, THU, FRI, SAT, SUN };
	enum islamic_month_codes_long { Muharram = 1, Safar, RabialAwwal, RabiathThani, JumadaalAwwal, JumadatTania, Rajab, Shaban, Ramadan, Shawwal, DhulQadah, DhulHijja	};
	enum hebrew_month_codes_long{Nisan=1, Iyyar, Sivan, ammuz,Av, Elul, Tishri, Heshvan,Kislev, Teveth, Shevat, Adar, Veadar};
	enum vulcan_month_codes_ling{
		Zat=1,
		Druh,
		KriBrax,
		reTKhutai,
		TkeKhuti,
		Khuti,
		TaKrat,
		Krilior,
		etkhior,
		Tlakht,
		TkeTas,
		Tasmeen,
	};


} // end-of-namespace khronos

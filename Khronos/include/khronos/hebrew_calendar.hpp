#pragma once

/**	@file khronos/hebrew_calendar.hpp
	@author Garth Santor
	@date 2013-09-26

	Hebrew calendar class.
	*/

#pragma once

	/**	@file khronos/Hebrew_calendar.hpp
		@author Garth Santor
		@date 2013-09-19

		Hebrew calendar functions and class declaration.
		*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/Julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <cstddef>
#include <string>

namespace khronos {

	// VALUES
	/*!	JD of the start of the Hebrew epoch. */
	constexpr jd_t HEBREW_EPOCH = 347'995.5;

	// FUNCTIONS

	jd_t	hebrew_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	jd_t	hebrew_to_jd(year_t year, month_t month, day_t day);
	void	jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	void	jd_to_hebrew(jd_t jd, year_t& year, month_t& month, day_t& day);

	/*!	Leap year test for Proleptic hebrew Calendar.
	\return 'true' if leap year, 'false' if not.
	\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	*/
	constexpr bool is_hebrew_leapyear(year_t year) {
		return ((7 * year + 1) % 19) < 7;
	}

	// OPERATIONS

	/** Provide the number of days in the month of the hebrew Calendar. */
	constexpr day_t hebrew_days_in_month(month_t month, bool isLeapYear) {
		return hebrew::hebrew_days_in_month(month, isLeapYear);
	}

	/** Provide the number of days in the month of the hebrew Calendar. */
	constexpr day_t hebrew_months_in_year(bool isLeapYear) {
		return hebrew::hebrew_months_in_year(isLeapYear);
	}


	/** Provide the name of the given month in the hebrew calendar. */
	constexpr char const* hebrew_month_name(month_t month) {
		return hebrew::hebrew_full_month_name_long(month);
	}

	/** Provide the value of delay of week in the hebrew calendar. */
	constexpr day_t hebrew_delay_of_week(year_t year) {
		long long mon = (235 * year - 234) / 19;
		long long part = 12084 + 13753 * mon;
		long long day = mon * 29 + (part / 25920);

		if (((3 * (day + 1)) % 7) < 3)
			day += 1;

		return day;
	}

	/** Provide the value of adjacent year in the hebrew calendar. */
	constexpr day_t hebrew_adjacent_year(year_t year) {
		long long last = hebrew_delay_of_week(year - 1);
		long long present = hebrew_delay_of_week(year);
		long long next = hebrew_delay_of_week(year + 1);
		long long days = 0;
		if (next - present == 356) {
			 days = 2;
		}
		else if (next - present != 356 && present - last == 382) {
			 days = 1;
		}
		return days;
	}

	/*!	Getting days in a year for Proleptic hebrew Calendar.
	\return days of the year.
	\param year [in] Astronomical year 
	*/
	inline int hebrew_days_in_year(year_t year) {
		int days = hebrew_to_jd(year + 1, 7, 1) - hebrew_to_jd(year, 7, 1);
		return days;
	}

	constexpr day_t hebrew_days_in_month( year_t year, month_t month) {
		int days;
		if (month == 2 || month == 4 || month == 6 || month == 10 || month == 13) {
			days = 29;
		}
		else if (month == 12 && !(is_hebrew_leapyear(year))) {
			days = 29;
		}
		else if (month == 8 && hebrew_days_in_year(year) % 10 != 5) {
			days = 29;
		}
		else if (month == 9 && hebrew_days_in_year(year) % 10 == 3) {
			days = 29;
		}
		else {
			days = 30;
		}
		return days;
	}
	


	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic hebrew Calendar Date class. */
	class Hebrew {
		year_t	year_ = 1;
		month_t	month_ = 1;
		day_t	day_ = 1;
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

		void from_jd(jd_t jd) {
			if (tod(jd) != 0.5) {
				jd_to_hebrew(jd, year_, month_, day_, hour_, minute_, second_);
			}
			else {
				jd_to_hebrew(jd, year_, month_, day_);
			}
		}

		jd_t to_jd() const {
			if (tod(hour_, minute_, second_) != 0.5) {
				return hebrew_to_jd(year_, month_, day_, hour_, minute_, second_);
			}
			else {
				return hebrew_to_jd(year_, month_, day_);
			}
		}


	public:
		Hebrew();
		~Hebrew() { ;; }

		/*! Get the year.
			\return Astronomical year. */
		constexpr year_t year() const { return year_; }

		/*! Get the month.
			\return Month number [1..12] */
		constexpr month_t month() const { return month_; }

		/*! Get the day of the month.
			\return Day of month number [1..31]. */
		constexpr day_t day() const { return day_; }

		/*! Get the hour of time.
			\return hour of time [1..24]. */
		constexpr hour_t hour() const { return hour_; }

		/*! Get the minute of time.
			\return minute of time  [0..59]. */
		constexpr minute_t minute() const { return minute_; }

		/*! Get the second of time.
			\return second of time [0..60]. */
		constexpr second_t second() const { return second_; }

		/*! Construct a Hebrew calendar date from year,month,day,[hour,minute,second]
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			\param hour [in]  hour of time [1..24]
			\param minute [in] minute of time [0..59]
			\param second [in] second of time [0..60]
			*/
		constexpr Hebrew(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) { (WTIMEOFDAY); }

		/*! Construct a Hebrew calendar date from year,month,day
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			*/
		constexpr Hebrew(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) { (NOTIMEOFDAY); }

		/** Construct a Hebrew date from Jd Day Number object.
			@param jd [in] Jd object.
			*/
		Hebrew(Jd const& jd) { from_jd(jd.jd()); }

		std::string to_string() const;

		/**	Implicit cast to Jd class. */
		constexpr operator Jd() const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Hebrew type. */
		Hebrew& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// block some operators
	private:
		Hebrew operator + (detail::packaged_year_real const&);
		Hebrew operator - (detail::packaged_year_real const&);
		Hebrew operator + (detail::packaged_month_real const&);
		Hebrew operator - (detail::packaged_month_real const&);

	};



	// OPERATORS
	// ====================
	/** Hebrew + (integer month) */
	Hebrew operator + (Hebrew const& dt, detail::packaged_month_integer const& month);

	/** Hebrew - (integer month) */
	inline Hebrew operator - (Hebrew const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Hebrew + (integer year) */
	Hebrew operator + (Hebrew const& dt, detail::packaged_year_integer const& year);

	/**	Hebrew - (integer year) */
	inline Hebrew operator - (Hebrew const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }



	///** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, khronos::Hebrew const& g) { return os << g.to_string(); }

}
#pragma once

/**	@file khronos/Islamic_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Islamic calendar class and functions.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/Julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <cstddef>
#include <string>

namespace khronos {

	

	// VALUES
	/*!	JD of the start of the Islamic epoch. */
	constexpr jd_t ISLAMIC_EPOCH = 1'948'439.5;

	// FUNCTIONS

	jd_t	islamic_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	jd_t	islamic_to_jd(year_t year, month_t month, day_t day);
	void	jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	void	jd_to_islamic(jd_t jd, year_t& year, month_t& month, day_t& day);

	/*!	Leap year test for Proleptic islamic Calendar.
	\return 'true' if leap year, 'false' if not.
	\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	*/
	constexpr bool is_islamic_leapyear(year_t year) {
		return ( ((11 * year + 14) % 30) < 11);
	}

	// OPERATIONS

	/** Provide the number of days in the month of the islamic Calendar. */
	constexpr day_t islamic_days_in_month(month_t month, bool isLeapYear) {
		return islamic::islamic_days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the islamic calendar. */
	constexpr char const* islamic_month_name(month_t month) {
		return islamic::islamic_month_name_long(month);
	}


	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic islamic Calendar Date class. */
	class Islamic {
		year_t	year_ = 1;
		month_t	month_ = 1;
		day_t	day_ = 1;
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

		void from_jd(jd_t jd) { jd_to_islamic(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return islamic_to_jd(year_, month_, day_, hour_, minute_, second_); }


	public:
		Islamic();
		~Islamic() { ;; }



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

		/*! Construct a Islamic calendar date from year,month,day,[hour,minute,second]
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			\param hour [in]  hour of time [1..24]
			\param minute [in] minute of time [0..59]
			\param second [in] second of time [0..60]
			*/
		constexpr Islamic(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) { (WTIMEOFDAY); }

		/*! Construct a Islamic calendar date from year,month,day
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			*/
		constexpr Islamic(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) { (NOTIMEOFDAY); }

		/** Construct a Islamic date from Jd Day Number object.
			@param jd [in] Jd object.
			*/
		Islamic(Jd const& jd) { from_jd(jd.jd()); }

		std::string to_string() const;

		/**	Implicit cast to Jd class. */
		constexpr operator Jd() const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Islamic type. */
		Islamic& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// block some operators
	private:
		Islamic operator + (detail::packaged_year_real const&);
		Islamic operator - (detail::packaged_year_real const&);
		Islamic operator + (detail::packaged_month_real const&);
		Islamic operator - (detail::packaged_month_real const&);

	};



	// OPERATORS
	// ====================
	/** Islamic + (integer month) */
	Islamic operator + (Islamic const& dt, detail::packaged_month_integer const& month);

	/** Islamic - (integer month) */
	inline Islamic operator - (Islamic const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Islamic + (integer year) */
	Islamic operator + (Islamic const& dt, detail::packaged_year_integer const& year);

	/**	Islamic - (integer year) */
	inline Islamic operator - (Islamic const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }



	///** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, khronos::Islamic const& g) { return os << g.to_string(); }

}
#pragma once

/**	@file khronos/julian_calendar.hpp
	@author Garth Santor
	@date 2013-09-19

	Julian calendar functions and class declaration.
	*/

#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/Julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <cstddef>
#include <string>

namespace khronos {

	// LITERALS
		/* UDL - converts a Julian year CE to an astronomical Gregorian year. */
	constexpr year_t operator ""_AD(unsigned long long JulianYearAD) { return static_cast<year_t>(JulianYearAD); }
	constexpr year_t operator ""_ad(unsigned long long JulianYearAD) { return static_cast<year_t>(JulianYearAD); }
	/* UDL - converts a Julian year BCE to an astronomical Gregorian year. */
	constexpr year_t operator ""_BC(unsigned long long JulianYearBC) { return -static_cast<year_t>(JulianYearBC) + 1; }
	constexpr year_t operator ""_bc(unsigned long long JulianYearBC) { return -static_cast<year_t>(JulianYearBC) + 1; }

	// VALUES
	/*!	JD of the start of the Julian epoch. */
	constexpr jd_t JULIAN_EPOCH = 1'721'423.5;

	// FUNCTIONS

	jd_t	julian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	jd_t	julian_to_jd(year_t year, month_t month, day_t day);
	void	jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	void	jd_to_julian(jd_t jd, year_t& year, month_t& month, day_t& day);

	/*!	Leap year test for Proleptic Julian Calendar.
	\return 'true' if leap year, 'false' if not.
	\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	*/
	constexpr bool is_julian_leapyear(year_t year) {
		return (year % 4 == 0);
	}

	// OPERATIONS

	/** Provide the number of days in the month of the Julian Calendar. */
	constexpr day_t julian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the Julian calendar. */
	constexpr char const* julian_month_name(month_t month) {
		return civil::month_name_long(month);
	}


	/** Provide the short name of the given month in the Julian calendar. */
	constexpr char const* julian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}
	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic Julian Calendar Date class. */
	class Julian {
		year_t	year_ = 1;
		month_t	month_ = 1;
		day_t	day_ = 1;
		hour_t hour_ = 12;
		minute_t minute_ = 0;
		second_t second_ = 0;

		void from_jd(jd_t jd) {
			if (tod(jd) != 0.5) {
				jd_to_julian(jd, year_, month_, day_, hour_, minute_, second_);
			}
			else {
				jd_to_julian(jd, year_, month_, day_);
			}
			}
			
		jd_t to_jd() const { 
			if (tod(hour_, minute_, second_) != 0.5) {
				return julian_to_jd(year_, month_, day_, hour_, minute_, second_);
			}
			else {
				return julian_to_jd(year_, month_, day_);
			}
		}


	public:
		Julian();
		~Julian() { ;; }



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

		/*! Construct a Julian calendar date from year,month,day,[hour,minute,second]
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			\param hour [in]  hour of time [1..24]
			\param minute [in] minute of time [0..59]
			\param second [in] second of time [0..60]
			*/
		constexpr Julian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) { (WTIMEOFDAY); }

		/*! Construct a Julian calendar date from year,month,day
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			*/
		constexpr Julian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) { (NOTIMEOFDAY); }

		/** Construct a Julian date from Jd Day Number object.
			@param jd [in] Jd object.
			*/
		Julian(Jd const& jd) { from_jd(jd.jd()); }

		std::string to_string() const;

		/**	Implicit cast to Jd class. */
		constexpr operator Jd() const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Julian type. */
		Julian& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// block some operators
	private:
		Julian operator + (detail::packaged_year_real const&);
		Julian operator - (detail::packaged_year_real const&);
		Julian operator + (detail::packaged_month_real const&);
		Julian operator - (detail::packaged_month_real const&);
	
	};



	// OPERATORS
	// ====================
	/** Julian + (integer month) */
	Julian operator + (Julian const& dt, detail::packaged_month_integer const& month);

	/** Julian - (integer month) */
	inline Julian operator - (Julian const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Julian + (integer year) */
	Julian operator + (Julian const& dt, detail::packaged_year_integer const& year);

	/**	Julian - (integer year) */
	inline Julian operator - (Julian const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	

	///** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, khronos::Julian const& g) { return os << g.to_string(); }

}
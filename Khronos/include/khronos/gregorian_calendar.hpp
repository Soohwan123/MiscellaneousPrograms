#pragma once
/*
khronos\gregorian_calendar.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library 'Gregorian calendar' declarations.
*/


#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/Julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <cstddef>
#include <string>


namespace khronos {
	// LITERALS
	/* UDL - converts a Gregorian year CE to an astronomical Gregorian year. */
	constexpr year_t operator ""_CE(unsigned long long gregorianYearCE) { return static_cast<year_t>(gregorianYearCE); }
	constexpr year_t operator ""_ce(unsigned long long gregorianYearCE) { return static_cast<year_t>(gregorianYearCE); }
	/* UDL - converts a Gregorian year BCE to an astronomical Gregorian year. */
	constexpr year_t operator ""_BCE(unsigned long long gregorianYearBCE) { return -static_cast<year_t>(gregorianYearBCE) + 1; }
	constexpr year_t operator ""_bce(unsigned long long gregorianYearBCE) { return -static_cast<year_t>(gregorianYearBCE) + 1; }

	// VALUES
	/*!	JD of the start of the Gregorian epoch. */
	constexpr jd_t GREGORIAN_EPOCH = 1'721'425.5;

	// FUNCTIONS

	jd_t	gregorian_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	jd_t	gregorian_to_jd(year_t year, month_t month, day_t day);
	void	jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	void	jd_to_gregorian(jd_t jd, year_t& year, month_t& month, day_t& day);

	/*!	Leap year test for Proleptic Gregorian Calendar.
	\return 'true' if leap year, 'false' if not.
	\param year [in] Astronomical year (1 CE = 1, 1 BCE = 0, 2 BCE = -1, etc.)
	*/
	constexpr bool is_gregorian_leapyear(year_t year) {
		return (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);
	}


	// OPERATIONS

	/** Provide the number of days in the month of the Gregorian Calendar. */
	constexpr day_t gregorian_days_in_month(month_t month, bool isLeapYear) {
		return civil::days_in_month(month, isLeapYear);
	}


	/** Provide the name of the given month in the Gregorian calendar. */
	constexpr char const* gregorian_month_name(month_t month) {
		return civil::month_name_long(month);
	}


	/** Provide the short name of the given month in the Gregorian calendar. */
	constexpr char const* gregorian_short_month_name(month_t month) {
		return civil::month_name_short(month);
	}




	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic Gregorian Calendar Date class. */
	class Gregorian {
		year_t	year_ = 1;
		month_t	month_ = 1;
		day_t	day_ = 1;
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;

		void from_jd(jd_t jd) { jd_to_gregorian(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return gregorian_to_jd(year_, month_, day_, hour_, minute_, second_); }
	

	public:
		Gregorian();
		~Gregorian() { ;; }



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

		/*! Construct a Gregorian calendar date from year,month,day,[hour,minute,second]
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			\param hour [in]  hour of time [1..24]
			\param minute [in] minute of time [0..59]
			\param second [in] second of time [0..60]
			*/
		constexpr Gregorian(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) { (WTIMEOFDAY); }

		/*! Construct a Gregorian calendar date from year,month,day
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..31]
			*/
		constexpr Gregorian(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) { (NOTIMEOFDAY); }

		/** Construct a Gregorian date from Jd Day Number object.
			@param jd [in] Jd object.
			*/
		Gregorian(Jd const& jd) { from_jd(jd.jd()); }

		std::string to_string() const;

		/**	Implicit cast to Jd class. */
		constexpr operator Jd() const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Gregorian type. */
		Gregorian& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// block some operators
	private:
		Gregorian operator + (detail::packaged_year_real const&);
		Gregorian operator - (detail::packaged_year_real const&);
		Gregorian operator + (detail::packaged_month_real const&);
		Gregorian operator - (detail::packaged_month_real const&);
		//Gregorian operator + (detail::packaged_day const&);
		//Gregorian operator - (detail::packaged_day const&);
		////Gregorian operator + (detail::packaged_week const&);
		////Gregorian operator - (detail::packaged_week const&);
		//Gregorian operator + (detail::packaged_hour const&);
		//Gregorian operator - (detail::packaged_hour const&);
		//Gregorian operator + (detail::packaged_minute const&);
		//Gregorian operator - (detail::packaged_minute const&);
		//Gregorian operator + (detail::packaged_second const&);
		//Gregorian operator - (detail::packaged_second const&);
	};



	// OPERATORS
	// ====================
	/** Gregorian + (integer month) */
	Gregorian operator + (Gregorian const& dt, detail::packaged_month_integer const& month);

	/** Gregorian - (integer month) */
	inline Gregorian operator - (Gregorian const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Gregorian + (integer year) */
	Gregorian operator + (Gregorian const& dt, detail::packaged_year_integer const& year);

	/**	Gregorian - (integer year) */
	inline Gregorian operator - (Gregorian const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); }

	///**	Gregorian + (day) */
	//Gregorian operator + (Gregorian const& dt, detail::packaged_day const& day);

	///**	Gregorian - (day) */
	//inline Gregorian operator - (Gregorian const& dt, detail::packaged_day const& day) { return dt + detail::packaged_day(-day.nDays_); }

	///**	Gregorian + (week) */
	//Gregorian operator + (Gregorian const& dt, detail::packaged_week const& week);

	///**	Gregorian - (week) */
	//inline Gregorian operator - (Gregorian const& dt, detail::packaged_week const& week) { return dt + detail::packaged_week(-week.nWeeks_); }

	/**	Gregorian + (hour) */
	//Gregorian operator + (Gregorian const& dt, detail::packaged_hour const& hour);

	///**	Gregorian - (hour) */
	//inline Gregorian operator - (Gregorian const& dt, detail::packaged_hour const& hour) { return dt + detail::packaged_hour(-hour.nHours_); }

	///**	Gregorian + (minute) */
	//Gregorian operator + (Gregorian const& dt, detail::packaged_minute const& minute);

	///**	Gregorian - (minute) */
	//inline Gregorian operator - (Gregorian const& dt, detail::packaged_minute const& minute) { return dt + detail::packaged_minute(-minute.nMinutes_); }

	///**	Gregorian + (second) */
	//Gregorian operator + (Gregorian const& dt, detail::packaged_second const& second);

	///**	Gregorian - (second) */
	//inline Gregorian operator - (Gregorian const& dt, detail::packaged_second const& second) { return dt + detail::packaged_second(-second.nSeconds_); }

	/////** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, khronos::Gregorian const& g) { return os << g.to_string(); }

} // end-of-namespace khronos

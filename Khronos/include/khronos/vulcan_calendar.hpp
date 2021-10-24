#pragma once

/**	@file vulcan.hpp
	@author Garth Santor
	@date 2014-09-29

	Vulcan calendar class and functions.
	*/


#include <khronos/def.hpp>
#include <khronos/calendar.hpp>
#include <khronos/julian_day.hpp>
#include <khronos/timeofday.hpp>
#include <cstddef>
#include <string>


namespace khronos {

	// VALUES
	/*!	JD of the start of the Vulcan epoch. */
	constexpr jd_t VULCAN_EPOCH = 173'651.6;

	// FUNCTIONS

	jd_t	vulcan_to_jd(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second);
	jd_t	vulcan_to_jd(year_t year, month_t month, day_t day);
	void	jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day, hour_t& hour, minute_t& minute, second_t& second);
	void	jd_to_vulcan(jd_t jd, year_t& year, month_t& month, day_t& day);


	// OPERATIONS



	/** Provide the name of the given month in the vulcan calendar. */
	constexpr char const* vulcan_month_name(month_t month) {
		return vulcan::vulcan_month_name_long(month);
	}

	/** Provide the days in a month in the vulcan calendar. */
	constexpr day_t vulcan_days_in_month() {
		return 21;
	}

	

	// CLASSES
	// --------------------------------------------------------------------------------------

	/**	Proleptic vulcan Calendar Date class. */
	class Vulcan {
		year_t	year_ = 1;
		month_t	month_ = 1;
		day_t	day_ = 1;
		hour_t hour_ = 0;
		minute_t minute_ = 0;
		second_t second_ = 0;
		day_t daysInMonth = 21;

		void from_jd(jd_t jd) { jd_to_vulcan(jd, year_, month_, day_, hour_, minute_, second_); }
		jd_t to_jd() const { return vulcan_to_jd(year_, month_, day_, hour_, minute_, second_); }


	public:
		Vulcan();
		~Vulcan() { ;; }



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


		

		/*! Construct a Vulcan calendar date from year,month,day,[hour,minute,second]
			*/
		constexpr Vulcan(year_t year, month_t month, day_t day, hour_t hour, minute_t minute, second_t second) : year_(year), month_(month), day_(day), hour_(hour), minute_(minute), second_(second) { (WTIMEOFDAY); }

		/*! Construct a Vulcan calendar date from year,month,day
			\param year [in] Astronomical year.
			\param month [in] Month number [1..12]
			\param day [in] Day of month [1..21]
			*/
		constexpr Vulcan(year_t year, month_t month, day_t day) : year_(year), month_(month), day_(day) { (NOTIMEOFDAY); }

		/** Construct a Vulcan date from Jd Day Number object.
			@param jd [in] Jd object.
			*/
		Vulcan(Jd const& jd) { from_jd(jd.jd()); }

		std::string to_string() const;

		/**	Implicit cast to Jd class. */
		constexpr operator Jd() const { return Jd(to_jd()); }


		/**	Assign and convert from Jd type to Vulcan type. */
		Vulcan& operator = (Jd const& jd) {
			from_jd(jd.jd());
			return *this;
		}

		// block some operators
	private:
		Vulcan operator + (detail::packaged_year_real const&);
		Vulcan operator - (detail::packaged_year_real const&);
		Vulcan operator + (detail::packaged_month_real const&);
		Vulcan operator - (detail::packaged_month_real const&);
	};

	/*!	Getting value functions for getting calendar values.
	\return each value accordingly
	\param Vulcan [Vulcan] g (constructor&)
	*/
	inline year_t year(Vulcan const& g) { return g.year(); }
	inline month_t month(Vulcan const& g) { return g.month(); }
	inline day_t day(Vulcan const& g) { return g.day(); }
	inline hour_t hour(Vulcan const& g) { return g.hour(); }
	inline minute_t minute(Vulcan const& g) { return g.minute(); }
	inline second_t second(Vulcan const& g) { return  g.second(); }

	// OPERATORS
	// ====================
	/** Vulcan + (integer month) */
	Vulcan operator + (Vulcan const& dt, detail::packaged_month_integer const& month);

	/** Vulcan - (integer month) */
	inline Vulcan operator - (Vulcan const& dt, detail::packaged_month_integer const& month) { return dt + detail::packaged_month_integer(-month.nMonths_); }

	/**	Vulcan + (integer year) */
	Vulcan operator + (Vulcan const& dt, detail::packaged_year_integer const& year);

	/**	Vulcan - (integer year) */
	inline Vulcan operator - (Vulcan const& dt, detail::packaged_year_integer const& year) { return dt + detail::packaged_year_integer(-year.nYears_); };

	/////** Stream insertion operator. */
	inline std::ostream& operator << (std::ostream& os, khronos::Vulcan const& g) { return os << g.to_string(); }

} // end-of-namespace khronos

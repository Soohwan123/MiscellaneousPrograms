#pragma once

/*
khronos\def.hpp
(c) Garth Santor
Created: 2015-09-22
Last Updated: 2015-09-22

Khronos library definitions.
*/

namespace khronos {
	// Note: fundamental data types are signed to simplifies subtractions. * /
	using second_t = double;
	using minute_t = int;
	using hour_t = int;

	using tod_t = double;

	using day_t = int;
	using month_t = int;
	using year_t = long long;

	using jd_t = double;

	/** Indicates the 'now' type used by default constructors. */
	enum now_t { NOTIMEOFDAY = 0, WTIMEOFDAY };

	// VALUES
	double constexpr EARTH_ORBITAL_PERIOD_DAYS = 365.256'363'004;
	double constexpr HOUR_TO_DAYS_CONST = 0.041'666'667;
	double constexpr MINUTE_TO_DAYS_CONST = 0.000'694'444;
	double constexpr SECOND_TO_DAYS_CONST = 0.000'011'574;

} // end-of-namespace khronos

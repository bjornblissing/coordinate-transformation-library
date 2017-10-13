/*
 * wgs84position.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include "wgs84position.h"
#include "gausskreuger.h"

#include <iostream>
#include <iomanip>
#include <limits> // std::numeric_limits
#include <algorithm> // std::replace
#include <iterator>
#include <sstream>
#include <vector>

namespace vti {

WGS84Position::WGS84Position(const std::string& positionString, WGS84Format format) : Position(Grid::WGS84)
{
	if (format == WGS84Format::Degrees) {
		std::string trimmedString = trim(positionString);
		std::stringstream stringStream(trimmedString);
		std::istream_iterator<std::string> begin(stringStream);
		std::istream_iterator<std::string> end;
		std::vector<std::string> lat_lon(begin, end);

		if (lat_lon.size() == 2) {
			// Convert eventual comma to dot
			std::string lat = lat_lon[0];
			std::string lon = lat_lon[1];
			std::replace(lat.begin(), lat.end(), ',', '.'); // Replace commas with dots
			std::replace(lon.begin(), lon.end(), ',', '.'); // Replace commas with dots
			// Convert string to double
			m_latitude = atof(lat.c_str());
			m_longitude = atof(lon.c_str());
		} else {
			std::cerr << "The position string is invalid" << std::endl;
		}
	} else if (format == WGS84Format::DegreesMinutes || format == WGS84Format::DegreesMinutesSeconds) {
		size_t firstValueEndPos = 0;

		if (format == WGS84Format::DegreesMinutes) {
			firstValueEndPos = positionString.find_first_of("'");
		} else if (format == WGS84Format::DegreesMinutesSeconds) {
			firstValueEndPos = positionString.find_first_of("\"");
		}

		std::string lat = trim(positionString.substr(0, firstValueEndPos + 1));
		std::string lon = trim(positionString.substr(firstValueEndPos + 1));
		setLatitudeFromString(lat, format);
		setLongitudeFromString(lon, format);
	}
}

void WGS84Position::setLatitudeFromString(std::string value, WGS84Format format)
{
	value = trim(value);

	if (format == WGS84Format::DegreesMinutes) {
		m_latitude = parseValueFromDmString(value, "S");
	} else if (format == WGS84Format::DegreesMinutesSeconds) {
		m_latitude = parseValueFromDmsString(value, "S");
	} else if (format == WGS84Format::Degrees) {
		m_latitude = atof(value.c_str());
	}
}

void WGS84Position::setLongitudeFromString(std::string value, WGS84Format format)
{
	value = trim(value);

	if (format == WGS84Format::DegreesMinutes) {
		m_longitude = parseValueFromDmString(value, "W");
	} else if (format == WGS84Format::DegreesMinutesSeconds) {
		m_longitude = parseValueFromDmsString(value, "W");
	} else if (format == WGS84Format::Degrees) {
		m_longitude = atof(value.c_str());
	}
}

std::string WGS84Position::latitudeToString(WGS84Format format)
{
	if (format == WGS84Format::DegreesMinutes) {
		return convToDmString(m_latitude, "N", "S");
	} else if (format == WGS84Format::DegreesMinutesSeconds) {
		return convToDmsString(m_latitude, "N", "S");
	} else {
		std::stringstream lat_ss;
		lat_ss << std::fixed << std::setprecision(10) << m_latitude;
		return lat_ss.str();
	}
}

std::string WGS84Position::longitudeToString(WGS84Format format)
{
	if (format == WGS84Format::DegreesMinutes) {
		return convToDmString(m_longitude, "E", "W");
	} else if (format == WGS84Format::DegreesMinutesSeconds) {
		return convToDmsString(m_longitude, "E", "W");
	} else {
		std::stringstream long_ss;
		long_ss << std::setprecision(10) << m_longitude;
		return long_ss.str();
	}
}

std::string WGS84Position::convToDmString(double value, const std::string& positiveValue, const std::string& negativeValue)
{
	if (value == std::numeric_limits<double>::min()) {
		return "";
	}

	double degrees = floor(std::abs(value));
	double minutes = (std::abs(value) - degrees) * 60;
	std::stringstream dmss;

	if (value >= 0) {
		dmss << positiveValue;
	} else {
		dmss << negativeValue;
	}

	dmss << " ";
	dmss << std::setprecision(0) << degrees;
	dmss << "º ";
	dmss << std::setprecision(0) << minutes;
	dmss << "'";
	return dmss.str();
}

std::string WGS84Position::convToDmsString(double value, const std::string& positiveValue, const std::string& negativeValue)
{
	if (value == std::numeric_limits<double>::min()) {
		return "";
	}

	double degrees = floor(std::abs(value));
	double minutes = floor((std::abs(value) - degrees) * 60);
	double seconds = (std::abs(value) - degrees - minutes / 60) * 3600;
	std::stringstream dmsss;

	if (value >= 0) {
		dmsss << positiveValue;
	} else {
		dmsss << negativeValue;
	}

	dmsss << " ";
	dmsss << std::fixed << std::setprecision(0) << degrees;
	dmsss << "º ";
	dmsss << std::fixed << std::setprecision(0) << minutes;
	dmsss << "' ";
	dmsss << std::fixed << std::setprecision(5) << seconds;
	dmsss << "\"";
	return dmsss.str();
}

double WGS84Position::parseValueFromDmString(std::string value, const std::string& positiveChar)
{
	double retVal = 0;

	if (!value.empty()) {
		std::string direction = value.substr(0, 1);
		value = value.substr(1);
		std::string degree = value.substr(0, value.find_first_of("º"));
		degree = trim(degree);
		value = value.substr(value.find_first_of("º") + 1);
		std::string minutes = value.substr(0, value.find_first_of("'"));
		std::replace(minutes.begin(), minutes.end(), ',', '.'); // Replace commas with dots
		minutes = trim(minutes);
		value = value.substr(value.find_first_of("'") + 1);
		retVal = atof(degree.c_str());
		retVal += atof(minutes.c_str()) / 60.0;

		if (retVal > 90) {
			retVal = std::numeric_limits<double>::min();
		}

		if (direction == positiveChar || direction == ("-")) {
			retVal *= -1;
		}
	} else {
		retVal = std::numeric_limits<double>::min();
	}

	return retVal;
}

double WGS84Position::parseValueFromDmsString(std::string value, const std::string& positiveChar)
{
	double retVal = 0;

	if (!value.empty()) {
		std::string direction = value.substr(0, 1);
		value = value.substr(1);
		std::string degree = value.substr(0, value.find_first_of("º"));
		degree = trim(degree);
		value = value.substr(value.find_first_of("º") + 1);
		std::string minutes = value.substr(0, value.find_first_of("'"));
		std::replace(minutes.begin(), minutes.end(), ',', '.'); // Replace commas with dots
		minutes = trim(minutes);
		value = value.substr(value.find_first_of("'") + 1);
		std::string seconds = value.substr(0, value.find_first_of("\""));
		std::replace(seconds.begin(), seconds.end(), ',', '.'); // Replace commas with dots
		seconds = trim(seconds);
		value = value.substr(value.find_first_of("'") + 1);
		retVal = atof(degree.c_str());
		retVal += atof(minutes.c_str()) / 60.0;
		retVal += atof(seconds.c_str()) / 3600.0;

		if (retVal > 90) {
			retVal = std::numeric_limits<double>::min();
		}

		if (direction == positiveChar || direction == ("-")) {
			retVal *= -1;
		}
	} else {
		retVal = std::numeric_limits<double>::min();
	}

	return retVal;
}

} // namespace vti

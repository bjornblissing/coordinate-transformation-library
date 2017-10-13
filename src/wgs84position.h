/*
 * wgs84position.h
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#ifndef _COORDINATE_WGS84POSITION_H_
#define _COORDINATE_WGS84POSITION_H_ 1

#include "position.h"


class WGS84Position : public Position {
	public:
		enum class WGS84Format { Degrees, DegreesMinutes, DegreesMinutesSeconds };
		/**
		* Create a new WGS84 position with empty coordinates
		*/
		WGS84Position() : Position(Grid::WGS84) {};
		/**
		* Create a new WGS84 position with latitude and longitude
		*/
		WGS84Position(double latitude, double longitude) : Position(latitude, longitude, Grid::WGS84) {}
		/**
		* Create a new WGS84 position from a String containing both latitude
		* and longitude. The string is parsed based on the supplied format.
		*/
		WGS84Position(const std::string& positionString, WGS84Format format);
		/**
		* Set the latitude value from a string. The string is parsed based on given format.
		*/
		void setLatitudeFromString(std::string value, WGS84Format format);
		/**
		* Set the longitude value from a string. The string is parsed based on given format.
		*/
		void setLongitudeFromString(std::string value, WGS84Format format);
		/**
		* Returns a string representation in the given format
		*/
		std::string latitudeToString(WGS84Format format);
		/**
		* Returns a string representation in the given format
		*/
		std::string longitudeToString(WGS84Format format);
	protected:
		static std::string convToDmString(double value, const std::string& positiveValue, const std::string& negativeValue);
		static std::string convToDmsString(double value, const std::string& positiveValue, const std::string& negativeValue);
		static double parseValueFromDmString(std::string value, const std::string& positiveChar);
		static double parseValueFromDmsString(std::string value, const std::string& positiveChar);
};

#endif // _COORDINATE_WGS84POSITION_H_
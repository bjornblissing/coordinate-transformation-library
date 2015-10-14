/*
 * position.h
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#ifndef _COORDINATE_POSITION_H_
#define _COORDINATE_POSITION_H_ 1

#include <string>

class Position {
	public:
		enum Grid { RT90, WGS84, SWEREF99, UNDEFINED};
		Position() : m_latitude(0.0), m_longitude(0.0), m_gridFormat(UNDEFINED) {};
		explicit Position(Grid format) : m_latitude(0.0), m_longitude(0.0), m_gridFormat(format) {}
		Position(double lat, double lon, Grid format) : m_latitude(lat), m_longitude(lon), m_gridFormat(format) {}
		double getLatitude() const { return m_latitude; }
		double getLongitude() const { return m_longitude; }
	protected:
		double m_latitude;
		double m_longitude;
		Grid m_gridFormat;

		static std::string trim(const std::string& str, const std::string& whitespace = " \t");
};

#endif //_COORDINATE_POSITION_H_
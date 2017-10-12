/*
 * rt90position.h
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#ifndef _COORDINATE_RT90POSITION_H_
#define _COORDINATE_RT90POSITION_H_ 1

#include "wgs84position.h"

class RT90Position : public Position {
	public:
		enum RT90Projection {
			rt90_7_5_gon_v,
			rt90_5_0_gon_v,
			rt90_2_5_gon_v,
			rt90_0_0_gon_v,
			rt90_2_5_gon_o,
			rt90_5_0_gon_o
		};

		/**
		* Create a new position using default projection (2.5 gon v)
		*/
		RT90Position(double x, double y) : Position(x, y, Grid::RT90), m_projection(RT90Projection::rt90_2_5_gon_v) { }

		/**
		* Create a new position
		*/
		RT90Position(double x, double y, RT90Projection projection) : Position(x, y, Grid::RT90), m_projection(projection) { }

		/**
		* Create a RT90 position by converting a WGS84 position
		*/
		RT90Position(WGS84Position position, RT90Projection rt90projection);

		/**
		* Convert position to WGS84 format
		*/
		WGS84Position toWGS84();

		/**
		* Get projection type as String
		* @return
		*/
		std::string getProjectionString()
		{
			return getProjectionString(m_projection);
		}

	protected:
		static std::string getProjectionString(RT90Projection projection);
		RT90Projection m_projection;
};
#endif //_COORDINATE_RT90POSITION_H_

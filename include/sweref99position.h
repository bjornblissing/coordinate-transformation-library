/*
 * sweref99position.h
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#ifndef _COORDINATE_SWEREF99POSITION_H_
#define _COORDINATE_SWEREF99POSITION_H_ 1

#include "wgs84position.h"

namespace vti {

class SWEREF99Position : public Position {
	public:
		enum class SWEREFProjection {
			sweref_99_tm,
			sweref_99_12_00,
			sweref_99_13_30,
			sweref_99_15_00,
			sweref_99_16_30,
			sweref_99_18_00,
			sweref_99_14_15,
			sweref_99_15_45,
			sweref_99_17_15,
			sweref_99_18_45,
			sweref_99_20_15,
			sweref_99_21_45,
			sweref_99_23_15
		};
		/**
		* Create a SWEREF99 position from double values with SWEEREF 99 TM as default projection
		*/
		SWEREF99Position(double n, double e) : Position(n, e, Grid::SWEREF99),  m_projection(SWEREFProjection::sweref_99_tm) {}

		/**
		* Create a SWEREF99 position from double values. Supply the projection for values
		* other than SWEREF 99 TM
		*/
		SWEREF99Position(double n, double e, SWEREFProjection projection) : Position(n, e, Grid::SWEREF99), m_projection(projection) {}

		/**
		* Create a SWEREF99 position by converting a WGS84 position
		*/
		SWEREF99Position(WGS84Position position, SWEREFProjection projection);

		/**
		* Convert the position to WGS84 format
		*/
		WGS84Position toWGS84();

		/**
		* Get projection type as String
		*/
		std::string getProjectionString()
		{
			return getProjectionString(m_projection);
		}

	protected:
		static std::string getProjectionString(SWEREFProjection projection);
		SWEREFProjection m_projection;
};

}

#endif // _COORDINATE_SWEREF99POSITION_H_

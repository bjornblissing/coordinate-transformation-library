/*
 * sweref99position.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include "sweref99position.h"
#include "gausskreuger.h"

SWEREF99Position::SWEREF99Position(WGS84Position position, SWEREFProjection projection) : Position(Grid::SWEREF99)
{
	GaussKreuger gkProjection;
	gkProjection.swedish_params(getProjectionString(projection));
	Coordinate lat_lon = gkProjection.geodetic_to_grid(position.getLatitude(), position.getLongitude());
	m_latitude = lat_lon.x;
	m_longitude = lat_lon.y;
	projection = projection;
}

WGS84Position SWEREF99Position::toWGS84()
{
	GaussKreuger gkProjection;
	gkProjection.swedish_params(getProjectionString(m_projection));
	Coordinate lat_lon = gkProjection.grid_to_geodetic(m_latitude, m_longitude);
	WGS84Position newPos(lat_lon.x, lat_lon.y);
	return newPos;
}

std::string SWEREF99Position::getProjectionString(SWEREFProjection projection)
{
	std::string retVal = "";

	switch (projection) {
		case sweref_99_tm:
			retVal = "sweref_99_tm";
			break;

		case sweref_99_12_00:
			retVal = "sweref_99_1200";
			break;

		case sweref_99_13_30:
			retVal = "sweref_99_1330";
			break;

		case sweref_99_14_15:
			retVal = "sweref_99_1415";
			break;

		case sweref_99_15_00:
			retVal = "sweref_99_1500";
			break;

		case sweref_99_15_45:
			retVal = "sweref_99_1545";
			break;

		case sweref_99_16_30:
			retVal = "sweref_99_1630";
			break;

		case sweref_99_17_15:
			retVal = "sweref_99_1715";
			break;

		case sweref_99_18_00:
			retVal = "sweref_99_1800";
			break;

		case sweref_99_18_45:
			retVal = "sweref_99_1845";
			break;

		case sweref_99_20_15:
			retVal = "sweref_99_2015";
			break;

		case sweref_99_21_45:
			retVal = "sweref_99_2145";
			break;

		case sweref_99_23_15:
			retVal = "sweref_99_2315";
			break;

		default:
			retVal = "sweref_99_tm";
			break;
	}

	return retVal;
}

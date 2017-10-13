/*
 * rt90position.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include "rt90position.h"
#include "gausskreuger.h"

namespace vti {

RT90Position::RT90Position(WGS84Position position, RT90Projection rt90projection) : Position(Grid::RT90)
{
	GaussKreuger gkProjection;
	gkProjection.swedish_params(getProjectionString(rt90projection));
	GaussKreuger::Coordinate lat_lon = gkProjection.geodetic_to_grid(position.getLatitude(), position.getLongitude());
	m_latitude = lat_lon.x;
	m_longitude = lat_lon.y;
	m_projection = rt90projection;
}

WGS84Position RT90Position::toWGS84()
{
	GaussKreuger gkProjection;
	gkProjection.swedish_params(getProjectionString());
	GaussKreuger::Coordinate lat_lon = gkProjection.grid_to_geodetic(m_latitude, m_longitude);
	WGS84Position newPos(lat_lon.x, lat_lon.y);
	return newPos;
}

std::string RT90Position::getProjectionString(RT90Projection projection)
{
	std::string retVal = "";

	switch (projection) {
		case RT90Projection::rt90_7_5_gon_v:
			retVal = "rt90_7.5_gon_v";
			break;

		case RT90Projection::rt90_5_0_gon_v:
			retVal = "rt90_5.0_gon_v";
			break;

		case RT90Projection::rt90_2_5_gon_v:
			retVal = "rt90_2.5_gon_v";
			break;

		case RT90Projection::rt90_0_0_gon_v:
			retVal = "rt90_0.0_gon_v";
			break;

		case RT90Projection::rt90_2_5_gon_o:
			retVal = "rt90_2.5_gon_o";
			break;

		case RT90Projection::rt90_5_0_gon_o:
			retVal = "rt90_5.0_gon_o";
			break;

		default:
			retVal = "rt90_2.5_gon_v";
			break;
	}

	return retVal;
}

} // namespace vti

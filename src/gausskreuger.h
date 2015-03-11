/*
 * gausskreuger.h
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#ifndef _COORDINATE_GAUSSKREUGER_H_
#define _COORDINATE_GAUSSKREUGER_H_ 1

#include <string>

struct Coordinate {
	Coordinate() : x(0), y(0) {}
	double x;
	double y;
};

class GaussKreuger {
	public:
		// Parameters for RT90 and SWEREF99TM.
		// Note: Parameters for RT90 are choosen to eliminate the
		// differences between Bessel and GRS80-ellipsoides.
		// Bessel-variants should only be used if lat/long are given as
		// RT90-lat/long based on the Bessel ellipsoide (from old maps).
		// Parameter: projection (std::string). Must match if-statement.
		void swedish_params(std::string projection);
		// Conversion from geodetic coordinates to grid coordinates.
		Coordinate geodetic_to_grid(double latitude, double longitude) const;
		// Conversion from grid coordinates to geodetic coordinates.
		Coordinate grid_to_geodetic(double x, double y) const;
	protected:
		void grs80_params();
		void bessel_params();
		void sweref99_params();

		static double atanh(double value);

		double m_axis; // Semi-major axis of the ellipsoid.
		double m_flattening; // Flattening of the ellipsoid.
		double m_central_meridian; // Central meridian for the projection.
		double m_scale; // Scale on central meridian.
		double m_false_northing; // Offset for origo.
		double m_false_easting; // Offset for origo.
};

#endif // _COORDINATE_GAUSSKREUGER_H_
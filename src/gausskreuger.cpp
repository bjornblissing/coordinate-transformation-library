/*
 * gausskreuger.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include "gausskreuger.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832
#endif

#include <limits>

namespace vti {

void GaussKreuger::swedish_params(const std::string& projection)
{
	// RT90 parameters, GRS 80 ellipsoid.
	if (projection == "rt90_7.5_gon_v") {
		grs80_params();
		m_central_meridian = 11.0 + 18.375 / 60.0;
		m_scale = 1.000006000000;
		m_false_northing = -667.282;
		m_false_easting = 1500025.141;
	} else if (projection == "rt90_5.0_gon_v") {
		grs80_params();
		m_central_meridian = 13.0 + 33.376 / 60.0;
		m_scale = 1.000005800000;
		m_false_northing = -667.130;
		m_false_easting = 1500044.695;
	} else if (projection == "rt90_2.5_gon_v") {
		grs80_params();
		m_central_meridian = 15.0 + 48.0 / 60.0 + 22.624306 / 3600.0;
		m_scale = 1.00000561024;
		m_false_northing = -667.711;
		m_false_easting = 1500064.274;
	} else if (projection == "rt90_0.0_gon_v") {
		grs80_params();
		m_central_meridian = 18.0 + 3.378 / 60.0;
		m_scale = 1.000005400000;
		m_false_northing = -668.844;
		m_false_easting = 1500083.521;
	} else if (projection == "rt90_2.5_gon_o") {
		grs80_params();
		m_central_meridian = 20.0 + 18.379 / 60.0;
		m_scale = 1.000005200000;
		m_false_northing = -670.706;
		m_false_easting = 1500102.765;
	} else if (projection == "rt90_5.0_gon_o") {
		grs80_params();
		m_central_meridian = 22.0 + 33.380 / 60.0;
		m_scale = 1.000004900000;
		m_false_northing = -672.557;
		m_false_easting = 1500121.846;
	} // RT90 parameters, Bessel 1841 ellipsoid.
	else if (projection == "bessel_rt90_7.5_gon_v") {
		bessel_params();
		m_central_meridian = 11.0 + 18.0 / 60.0 + 29.8 / 3600.0;
	} else if (projection == "bessel_rt90_5.0_gon_v") {
		bessel_params();
		m_central_meridian = 13.0 + 33.0 / 60.0 + 29.8 / 3600.0;
	} else if (projection == "bessel_rt90_2.5_gon_v") {
		bessel_params();
		m_central_meridian = 15.0 + 48.0 / 60.0 + 29.8 / 3600.0;
	} else if (projection == "bessel_rt90_0.0_gon_v") {
		bessel_params();
		m_central_meridian = 18.0 + 3.0 / 60.0 + 29.8 / 3600.0;
	} else if (projection == "bessel_rt90_2.5_gon_o") {
		bessel_params();
		m_central_meridian = 20.0 + 18.0 / 60.0 + 29.8 / 3600.0;
	} else if (projection == "bessel_rt90_5.0_gon_o") {
		bessel_params();
		m_central_meridian = 22.0 + 33.0 / 60.0 + 29.8 / 3600.0;
	} // SWEREF99TM and SWEREF99ddmm parameters.
	else if (projection == "sweref_99_tm") {
		sweref99_params();
		m_central_meridian = 15.00;
		m_scale = 0.9996;
		m_false_northing = 0.0;
		m_false_easting = 500000.0;
	} else if (projection == "sweref_99_1200") {
		sweref99_params();
		m_central_meridian = 12.00;
	} else if (projection == "sweref_99_1330") {
		sweref99_params();
		m_central_meridian = 13.50;
	} else if (projection == "sweref_99_1500") {
		sweref99_params();
		m_central_meridian = 15.00;
	} else if (projection == "sweref_99_1630") {
		sweref99_params();
		m_central_meridian = 16.50;
	} else if (projection == "sweref_99_1800") {
		sweref99_params();
		m_central_meridian = 18.00;
	} else if (projection == "sweref_99_1415") {
		sweref99_params();
		m_central_meridian = 14.25;
	} else if (projection == "sweref_99_1545") {
		sweref99_params();
		m_central_meridian = 15.75;
	} else if (projection == "sweref_99_1715") {
		sweref99_params();
		m_central_meridian = 17.25;
	} else if (projection == "sweref_99_1845") {
		sweref99_params();
		m_central_meridian = 18.75;
	} else if (projection == "sweref_99_2015") {
		sweref99_params();
		m_central_meridian = 20.25;
	} else if (projection == "sweref_99_2145") {
		sweref99_params();
		m_central_meridian = 21.75;
	} else if (projection == "sweref_99_2315") {
		sweref99_params();
		m_central_meridian = 23.25;
	} else {
		m_central_meridian = std::numeric_limits<double>::min();
	}
}

void GaussKreuger::grs80_params()
{
	m_axis = 6378137.0; // GRS 80.
	m_flattening = 1.0 / 298.257222101; // GRS 80.
	m_central_meridian = std::numeric_limits<double>::min();
}

void GaussKreuger::bessel_params()
{
	m_axis = 6377397.155; // Bessel 1841.
	m_flattening = 1.0 / 299.1528128; // Bessel 1841.
	m_central_meridian = std::numeric_limits<double>::min();
	m_scale = 1.0;
	m_false_northing = 0.0;
	m_false_easting = 1500000.0;
}

void GaussKreuger::sweref99_params()
{
	m_axis = 6378137.0; // GRS 80.
	m_flattening = 1.0 / 298.257222101; // GRS 80.
	m_central_meridian = std::numeric_limits<double>::min();
	m_scale = 1.0;
	m_false_northing = 0.0;
	m_false_easting = 150000.0;
}

GaussKreuger::Coordinate GaussKreuger::geodetic_to_grid(double latitude, double longitude) const
{
	Coordinate x_y;
	// Prepare ellipsoid-based stuff.
	double e2 = m_flattening * (2.0 - m_flattening);
	double n = m_flattening / (2.0 - m_flattening);
	double a_roof = m_axis / (1.0 + n) * (1.0 + n * n / 4.0 + n * n * n * n / 64.0);
	double A = e2;
	double B = (5.0 * e2 * e2 - e2 * e2 * e2) / 6.0;
	double C = (104.0 * e2 * e2 * e2 - 45.0 * e2 * e2 * e2 * e2) / 120.0;
	double D = (1237.0 * e2 * e2 * e2 * e2) / 1260.0;
	double beta1 = n / 2.0 - 2.0 * n * n / 3.0 + 5.0 * n * n * n / 16.0 + 41.0 * n * n * n * n / 180.0;
	double beta2 = 13.0 * n * n / 48.0 - 3.0 * n * n * n / 5.0 + 557.0 * n * n * n * n / 1440.0;
	double beta3 = 61.0 * n * n * n / 240.0 - 103.0 * n * n * n * n / 140.0;
	double beta4 = 49561.0 * n * n * n * n / 161280.0;
	// Convert.
	double deg_to_rad = M_PI / 180.0;
	double phi = latitude * deg_to_rad;
	double lambda = longitude * deg_to_rad;
	double lambda_zero = m_central_meridian * deg_to_rad;
	double phi_star = phi - sin(phi) * cos(phi) * (A +
					  B * pow(sin(phi), 2) +
					  C * pow(sin(phi), 4) +
					  D * pow(sin(phi), 6));
	double delta_lambda = lambda - lambda_zero;
	double xi_prim = atan(tan(phi_star) / cos(delta_lambda));
	double eta_prim = atanh(cos(phi_star) * sin(delta_lambda));
	double x = m_scale * a_roof * (xi_prim +
								   beta1 * sin(2.0 * xi_prim) * cosh(2.0 * eta_prim) +
								   beta2 * sin(4.0 * xi_prim) * cosh(4.0 * eta_prim) +
								   beta3 * sin(6.0 * xi_prim) * cosh(6.0 * eta_prim) +
								   beta4 * sin(8.0 * xi_prim) * cosh(8.0 * eta_prim)) +
			   m_false_northing;
	double y = m_scale * a_roof * (eta_prim +
								   beta1 * cos(2.0 * xi_prim) * sinh(2.0 * eta_prim) +
								   beta2 * cos(4.0 * xi_prim) * sinh(4.0 * eta_prim) +
								   beta3 * cos(6.0 * xi_prim) * sinh(6.0 * eta_prim) +
								   beta4 * cos(8.0 * xi_prim) * sinh(8.0 * eta_prim)) +
			   m_false_easting;
	x_y.x = round(x * 1000.0) / 1000.0;
	x_y.y = round(y * 1000.0) / 1000.0;
	return x_y;
}

GaussKreuger::Coordinate GaussKreuger::grid_to_geodetic(double x, double y) const
{
	Coordinate lat_lon;

	if (m_central_meridian == std::numeric_limits<double>::min()) {
		lat_lon.x = 0;
		lat_lon.y = 0;
		return lat_lon;
	}

	// Prepare ellipsoid-based stuff.
	double e2 = m_flattening * (2.0 - m_flattening);
	double n = m_flattening / (2.0 - m_flattening);
	double a_roof = m_axis / (1.0 + n) * (1.0 + n * n / 4.0 + n * n * n * n / 64.0);
	double delta1 = n / 2.0 - 2.0 * n * n / 3.0 + 37.0 * n * n * n / 96.0 - n * n * n * n / 360.0;
	double delta2 = n * n / 48.0 + n * n * n / 15.0 - 437.0 * n * n * n * n / 1440.0;
	double delta3 = 17.0 * n * n * n / 480.0 - 37 * n * n * n * n / 840.0;
	double delta4 = 4397.0 * n * n * n * n / 161280.0;
	double Astar = e2 + e2 * e2 + e2 * e2 * e2 + e2 * e2 * e2 * e2;
	double Bstar = -(7.0 * e2 * e2 + 17.0 * e2 * e2 * e2 + 30.0 * e2 * e2 * e2 * e2) / 6.0;
	double Cstar = (224.0 * e2 * e2 * e2 + 889.0 * e2 * e2 * e2 * e2) / 120.0;
	double Dstar = -(4279.0 * e2 * e2 * e2 * e2) / 1260.0;
	// Convert.
	double deg_to_rad = M_PI / 180;
	double lambda_zero = m_central_meridian * deg_to_rad;
	double xi = (x - m_false_northing) / (m_scale * a_roof);
	double eta = (y - m_false_easting) / (m_scale * a_roof);
	double xi_prim = xi -
					 delta1 * sin(2.0 * xi) * cosh(2.0 * eta) -
					 delta2 * sin(4.0 * xi) * cosh(4.0 * eta) -
					 delta3 * sin(6.0 * xi) * cosh(6.0 * eta) -
					 delta4 * sin(8.0 * xi) * cosh(8.0 * eta);
	double eta_prim = eta -
					  delta1 * cos(2.0 * xi) * sinh(2.0 * eta) -
					  delta2 * cos(4.0 * xi) * sinh(4.0 * eta) -
					  delta3 * cos(6.0 * xi) * sinh(6.0 * eta) -
					  delta4 * cos(8.0 * xi) * sinh(8.0 * eta);
	double phi_star = asin(sin(xi_prim) / cosh(eta_prim));
	double delta_lambda = atan(sinh(eta_prim) / cos(xi_prim));
	double lon_radian = lambda_zero + delta_lambda;
	double lat_radian = phi_star + sin(phi_star) * cos(phi_star) *
						(Astar +
						 Bstar * pow(sin(phi_star), 2) +
						 Cstar * pow(sin(phi_star), 4) +
						 Dstar * pow(sin(phi_star), 6));
	lat_lon.x = lat_radian * 180.0 / M_PI;
	lat_lon.y = lon_radian * 180.0 / M_PI;
	return lat_lon;
}

} // namespace vti

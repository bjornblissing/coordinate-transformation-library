/*
 * tests.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include <iostream>
#include <cmath>

#include "rt90position.h"
#include "sweref99position.h"


bool compareWithEpsilon(double a, double b, double epsilon)
{
	return fabs(a - b) < epsilon;
}

int testRT90ToWGS84()
{
	RT90Position position(6583052, 1627548);
	WGS84Position wgsPos = position.toWGS84();
	// Values from Hitta.se for the conversion
	double latFromHitta = 59.3489;
	double lonFromHitta = 18.0473;
	double lat = round(wgsPos.getLatitude() * 10000) / 10000.0;
	double lon = round(wgsPos.getLongitude() * 10000) / 10000.0;

	if (!compareWithEpsilon(latFromHitta, lat, 0.00001)) {
		std::cerr << "Latitude calculation failed." << std::endl;
		return -1;
	}

	if (!compareWithEpsilon(lonFromHitta, lon, 0.00001)) {
		std::cerr << "Longitude calculation failed." << std::endl;
		return -1;
	}

	// String values from Lantmateriet.se, they convert DMS only.
	// Reference: http://www.lantmateriet.se/templates/LMV_Enkelkoordinattransformation.aspx?id=11500
	std::string latDmsStringFromLM = "N 59º 20' 56.09287\"";
	std::string lonDmsStringFromLM = "E 18º 2' 50.34806\"";
	std::string latDmsStringFromWGS = wgsPos.latitudeToString(WGS84Position::WGS84Format::DegreesMinutesSeconds);
	std::string longDmsStringFromWGS = wgsPos.longitudeToString(WGS84Position::WGS84Format::DegreesMinutesSeconds);

	if (latDmsStringFromLM != latDmsStringFromWGS) {
		std::cerr << "Could not create latitude DMS string" << std::endl;
		return -1;
	}

	if (lonDmsStringFromLM != longDmsStringFromWGS) {
		std::cerr << "Could not create latitude DMS string" << std::endl;
		return -1;
	}

	return 0;
}

int testWGS84ToRT90()
{
	WGS84Position wgsPos("N 59º 58' 55.23\" E 017º 50' 06.12\"", WGS84Position::WGS84Format::DegreesMinutesSeconds);
	RT90Position rtPos(wgsPos, RT90Position::RT90Projection::rt90_2_5_gon_v);
	// Conversion values from Lantmateriet.se, they convert from DMS only.
	// Reference: http://www.lantmateriet.se/templates/LMV_Enkelkoordinattransformation.aspx?id=11500
	double xPosFromLM = 6653174.343;
	double yPosFromLM = 1613318.742;
	double lat = round(rtPos.getLatitude() * 1000) / 1000.0;
	double lon = round(rtPos.getLongitude() * 1000) / 1000.0;

	if (!compareWithEpsilon(lat, xPosFromLM, 0.0001)) {
		std::cerr << "Latitude calculation failed." << std::endl;
		return -1;
	}

	if (!compareWithEpsilon(lon, yPosFromLM, 0.0001)) {
		std::cerr << "Longitude calculation failed." << std::endl;
		return -1;
	}

	return 0;
}
int testWGS84ToSweRef()
{
	WGS84Position wgsPos;
	wgsPos.setLatitudeFromString("N 59º 58' 55.23\"", WGS84Position::WGS84Format::DegreesMinutesSeconds);
	wgsPos.setLongitudeFromString("E 017º 50' 06.12\"", WGS84Position::WGS84Format::DegreesMinutesSeconds);
	SWEREF99Position rtPos(wgsPos, SWEREF99Position::SWEREFProjection::sweref_99_tm);
	// Conversion values from Lantmateriet.se, they convert from DMS only.
	// Reference: http://www.lantmateriet.se/templates/LMV_Enkelkoordinattransformation.aspx?id=11500
	double xPosFromLM = 6652797.165;
	double yPosFromLM = 658185.201;
	double lat = round(rtPos.getLatitude() * 1000) / 1000.0;
	double lon = round(rtPos.getLongitude() * 1000) / 1000.0;

	if (!compareWithEpsilon(lat, xPosFromLM, 0.0001)) {
		std::cerr << "Latitude calculation failed." << std::endl;
		return -1;
	}

	if (!compareWithEpsilon(lon, yPosFromLM, 0.0001)) {
		std::cerr << "Longitude calculation failed." << std::endl;
		return -1;
	}

	return 0;
}
int testSweRefToWGS84()
{
	SWEREF99Position swePos(6652797.165, 658185.201);
	WGS84Position wgsPos = swePos.toWGS84();
	// String values from Lantmateriet.se, they convert DMS only.
	// Reference: http://www.lantmateriet.se/templates/LMV_Enkelkoordinattransformation.aspx?id=11500
	std::string latDmsStringFromLM = "N 59º 58' 55.23001\"";
	std::string lonDmsStringFromLM = "E 17º 50' 6.11997\"";
	std::string latDmsStringFromWGS = wgsPos.latitudeToString(WGS84Position::WGS84Format::DegreesMinutesSeconds);
	std::string longDmsStringFromWGS = wgsPos.longitudeToString(WGS84Position::WGS84Format::DegreesMinutesSeconds);

	if (latDmsStringFromLM != latDmsStringFromWGS) {
		std::cerr << "Could not create latitude DMS string" << std::endl;
		return -1;
	}

	if (lonDmsStringFromLM != longDmsStringFromWGS) {
		std::cerr << "Could not create latitude DMS string" << std::endl;
		return -1;
	}

	return 0;
}
int testWGS84Parse()
{
	// Values from Eniro.se
	WGS84Position wgsPosDM("N 62º 10.560' E 015º 54.180'", WGS84Position::WGS84Format::DegreesMinutes);;
	WGS84Position wgsPosDMs("N 62º 10' 33.60\" E 015º 54' 10.80\"", WGS84Position::WGS84Format::DegreesMinutesSeconds);
	double lat = round(wgsPosDM.getLatitude() * 1000) / 1000.0;
	double lon = round(wgsPosDM.getLongitude() * 1000) / 1000.0;

	if (!compareWithEpsilon(62.176, lat, 0.0001)) {
		std::cerr << "Latitude calculation failed." << std::endl;
		return -1;
	}

	if (!compareWithEpsilon(15.903, lon, 0.0001)) {
		std::cerr << "Longitude calculation failed." << std::endl;
		return -1;
	}

	double lat_s = round(wgsPosDMs.getLatitude() * 1000) / 1000.0;
	double lon_s = round(wgsPosDMs.getLongitude() * 1000) / 1000.0;

	if (!compareWithEpsilon(62.176, lat_s, 0.0001)) {
		std::cerr << "Latitude calculation failed." << std::endl;
		return -1;
	}

	if (!compareWithEpsilon(15.903, lon_s, 0.0001)) {
		std::cerr << "Longitude calculation failed." << std::endl;
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cerr << "Unknown test number" << std::endl;
		return -1;
	}

	int retVal = -1;
	// Get test number
	int testNumber = atoi(argv[1]);

	switch (testNumber) {
		case 1:
			retVal = testRT90ToWGS84();
			break;

		case 2:
			retVal = testWGS84ToRT90();
			break;

		case 3:
			retVal = testWGS84ToSweRef();
			break;

		case 4:
			retVal = testSweRefToWGS84();
			break;

		case 5:
			retVal = testWGS84Parse();
			break;

		default:
			std::cerr << "Unknown test" << std::endl;
			break;
	}

	return retVal;
}

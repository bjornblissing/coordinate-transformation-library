/*
 * position.cpp
 *
 *  Created on: March 11, 2015
 *      Author: Bjorn Blissing
 */

#include "position.h"

std::string Position::trim(const std::string& str, const std::string& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);

	if (strBegin == std::string::npos) {
		return "";    // no content
	}

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;
	return str.substr(strBegin, strRange);
}

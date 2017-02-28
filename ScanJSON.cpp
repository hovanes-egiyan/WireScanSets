/*
 * ScanJSON.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: Hovanes Egiyan
 */

#include "ScanJSON.hh"

using namespace std;

namespace WireScanSets {
// Map of required attributes for a JSON describing a scan
vector<string> ScanJSON::neededAttributes = { "date", "location", "dispersion", "results" };
// Map showing the pathlength for various harp location from 5C11 harp in mm-s.
map<string,double> ScanJSON::scannerPositions = {
		{"5C11"		, 0			},
		{"5C11B"	, 12163		},
		{"Radiator"	, 16420		},
		{"AD00C"	, 36000		}
	};
} /* namespace WireScanSets */

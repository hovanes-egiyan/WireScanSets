/*
 * ScanResultsJSON.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

#include "ScanResultJSON.hh"

namespace WireScanSets {
std::string ScanResultJSON::dataType = "result";
// Map of needed attributes
std::vector<std::string> ScanResultJSON::neededAttributes = { "datatype", "direction", "emittance", "data" };
} /* namespace WireScanSets */

/*
 * ScanSetJSON.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

#include "ScanSetJSON.hh"

using namespace std;

namespace WireScanSets {

vector<string> ScanSetJSON::neededAttributes = { "date", "location", "results" };
map<string,double> ScanSetJSON::scannerPositions = { {"5C11",0.0}, {"5C11B",12.0}, {"Radiator", 16}};

} /* namespace WireScanSets */

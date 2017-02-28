/*
 * ScanJSON.h
 *
 *  Created on: Feb 27, 2017
 *      Author: hovanes
 */

#ifndef SCANJSON_HH_
#define SCANJSON_HH_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include<vector>

#include <json/json.h>

#include "ScanResultJSON.hh"
#include "ScanSet.hh"
#include "Scan.hh"

namespace WireScanSets {

class ScanJSON: public Scan {
protected:
	// these are attributes needed for ScanSetJSON class
	static std::vector<std::string> neededAttributes;

	// map with positions for various scanners
	static std::map<std::string, double> scannerPositions;

	virtual void buildObjectFromJSON(Json::Value& jsonData) {
		// Verify that all required attributes exist
		for (auto& attrib : neededAttributes) {
			if (!jsonData.isMember(attrib)) {
				std::string errMsg = std::string("JSON missing attribute <")
						+ attrib + ">";
				throw std::runtime_error(errMsg);
			}
		}
		std::cout << "Will call Scan constructor with arguments : " << std::endl;
		;
		for (auto& attrib : neededAttributes) {
			std::cout << attrib << " : " << jsonData[attrib] << std::endl;
		}
		std::cout << std::endl;

		// Check that the location is a known location
		if (scannerPositions.count(jsonData["location"].asString()) < 1) {
			std::string errMsg = std::string("Unknown scan location <")
					+ jsonData["location"].asString() + ">";
			throw std::runtime_error(errMsg);
		}
		// Create a new object of the base class and assign the value to this
		std::string name = jsonData["location"].asString() + "-"
				+ jsonData["date"].asString();

		double disp = jsonData["dispersion"].asDouble();
		// Loop over all results and create ScanResult objects
		double zPosition = getZ(jsonData["location"].asString());
		std::map<std::string, ScanResult*> results;
		for (auto& resultObjJSON : jsonData["results"]) {
			try {
				ScanResultJSON* jsonResult = new ScanResultJSON(resultObjJSON,
						zPosition);
				results[jsonResult->GetName()] = jsonResult;
			} catch (std::runtime_error& e) {
				throw e;
			}
		}
		// Create a Scan objects with previously filled map of result objects.
		std::cout << "Creating Scan object " << std::endl;
		*dynamic_cast<Scan*>(this) = *(new Scan(name, results, disp ));
		// Clear the newly created map since the Scan objects creates a copy of the results map with
		// new pointers in it.
		results.clear();
	}

public:
	ScanJSON(Json::Value& jsonData) :
			Scan() {
		buildObjectFromJSON(jsonData);
	}

	ScanJSON(const std::string& fileName) :
			Scan() {
		std::cout << "Reading scan from " << fileName << std::endl;
		std::ifstream ifs(fileName);
		if (!ifs.is_open()) {
			std::string errMsg = "Could not find file " + fileName;
			throw std::runtime_error(errMsg);
		}
		std::cout << "  Found JSON file " << fileName << std::endl;
		Json::Value scanJSON;
		Json::Reader reader;
		bool parsing_success = reader.parse(ifs, scanJSON);

		if (!parsing_success) {
			std::string errMsg = "Parsing failed for file " + fileName;
			throw std::runtime_error(errMsg);
		}
		std::cout << "  Parsing successful\n";

		buildObjectFromJSON(scanJSON);
	}

	virtual ~ScanJSON() {
		// TODO Auto-generated destructor stub
	}

	virtual double getZ(std::string location) {
		if (scannerPositions.count(location) > 0)
			return scannerPositions[location];
		else
			throw std::runtime_error("Bad location error");
	}

};

} /* namespace WireScanSets */

#endif /* SCANJSON_HH_ */

/*
 * ScanResultsJSON.hh
 *
 *  Created on: Feb 24, 2017
 *      Author: hovanes
 */

#ifndef SCANRESULTJSON_HH_
#define SCANRESULTJSON_HH_

#include <iostream>
#include <fstream>
#include <string>

#include <json/json.h>

#include "ScanResult.hh"

namespace WireScanSets {

class ScanResultJSON: public ScanResult {
private:
	class ScanData {
	protected:
		double sigma = 0;
		double delta = 0;
	public:
		ScanData(Json::Value& jsonData) {
			if (jsonData.isMember("sigma")) {
				sigma = jsonData["sigma"].asDouble();
			}
			if (jsonData.isMember("delta")) {
				delta = jsonData["delta"].asDouble();
			}
		}
		virtual double getSigma() const {
			return sigma;
		}
		virtual double getDelta() const {
			return delta;
		}
	};
protected:
	// these are attributes needed for ScanSetJSON class
	static std::vector<std::string> neededAttributes;

	// Value for the attribute datatype in JSON
	static std::string dataType ;

	virtual void buildObjectFromJSON(Json::Value& jsonData, double zLocation) {
		// Verify that all required attributes exist
		for (auto& attrib : neededAttributes) {
			if (!jsonData.isMember(attrib)) {
				std::string errMsge = std::string("JSON missing attribute <")
						+ attrib + ">";
				throw std::runtime_error(errMsge);
			}
		}
		if( jsonData["datatype"].asString() != dataType ) {
			std::string errMsg = std::string("Expected datatype <")
					+ dataType + "> but got " + jsonData[""].asString() + ">";
			throw std::runtime_error(errMsg);
		}
		std::cout << "Will call ScanResult constructor with arguments : " << std::endl;
		;
		for (auto& attrib : neededAttributes) {
			std::cout << attrib << " : " << jsonData[attrib] << std::endl;
		}
		std::cout << std::endl;
		// Create a new object of the base class and assign the value to this
		std::string name = jsonData["direction"].asString();

		double emit = jsonData["emittance"].asDouble();

		ScanData data = jsonData["data"];

		*dynamic_cast<ScanResult*>(this) = *(new ScanResult(name, zLocation,
				emit, data.getSigma(), data.getDelta()));
		return;
	}

public:
	ScanResultJSON(Json::Value& jsonData, double zLocation) :
			ScanResult() {
		buildObjectFromJSON(jsonData, zLocation);
	}
	virtual ~ScanResultJSON() {
	}

	static std::vector<std::string>& getNeededAttributes() {
		return neededAttributes;
	}

	static void setNeededAttributes(std::vector<std::string>& attrib) {
		neededAttributes = attrib;
	}
};

} /* namespace WireScanSets */

#endif /* SCANRESULTJSON_HH_ */

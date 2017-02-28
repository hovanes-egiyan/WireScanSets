/*
 * Scan.hh
 *
 *  Created on: Feb 27, 2017
 *      Author: hovanes
 */

#ifndef SCAN_HH_
#define SCAN_HH_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "TNamed.h"

#include "BoundaryFunctionOfEmittance.hh"
#include "FunctionOfEmittance.hh"
#include "DerivativeFunctionOfEpsilon.hh"
#include "ScanResult.hh"

namespace WireScanSets {

class Scan: public TNamed {
protected:
	// Map of the scan results
	std::map<std::string, ScanResult*> scanMap;
	// Dispersion during thus scan
	double dispersion = 0;

public:
	// Default constructor
	Scan(const std::string name = "") :
			TNamed(name, name) {
	}
	// Main constructor, receives the name and the map of results.
	Scan(const std::string name, std::map<std::string, ScanResult*>& resultMap, double disp ) :
			TNamed(name, name), scanMap(), dispersion(disp) {
		// Deep-copy the content of the resultMap
		for (auto& scanIter : resultMap) {
			auto resultName = scanIter.first;
			auto resultPtr = scanIter.second;
			scanMap[resultName] = new ScanResult(*resultPtr);
		}
	}
	// Copy constructor
	Scan(const Scan& scan) :
			TNamed() {
		// Copy the TNamed part using Clone.
		*dynamic_cast<TNamed*>(this) =
				*dynamic_cast<TNamed*>(scan.Clone(
						(std::string("clonOf_") + std::string(scan.GetName())).c_str()));
		// Deep-copy the map of results of the scan object
		for (auto& oldScanIter : scan.scanMap) {
			auto& rName = oldScanIter.first;
			auto& resultPtr = oldScanIter.second;
			scanMap[rName] = new ScanResult(*resultPtr);
		}
		dispersion = scan.dispersion;
	}

	// Assignment operator
	Scan& operator=( const Scan& scan ) {
		if( this == &scan ) return *this;
		// Copy the TNamed part using Clone.
		*dynamic_cast<TNamed*>(this) =
				*dynamic_cast<TNamed*>(scan.Clone(
						(std::string("clonOf_") + std::string(scan.GetName())).c_str()));
		// Clear the existing map of results.
		scanMap.clear();
		// Deep-copy the map of results of the scan object in the argument
		for (auto& oldScanIter : scan.scanMap) {
			auto& rName = oldScanIter.first;
			auto& resultPtr = oldScanIter.second;
			scanMap[rName] = new ScanResult(*resultPtr);
		}
		dispersion = scan.dispersion;
		return *this;
	}

	virtual void addResult(ScanResult& result) {
		scanMap[result.GetName()] = new ScanResult(result);
	}

	virtual ScanResult* getResult( std::string name ) {
		if( scanMap.count( name ) > 0 ) return scanMap[name];
		else return nullptr;
	}

	virtual ~Scan() {
		scanMap.clear();
	}

	virtual const std::map<std::string, ScanResult*>& getScanMap() const {
		return scanMap;
	}

	virtual void setScanMap(const std::map<std::string, ScanResult*>& scanMap) {
		this->scanMap = scanMap;
	}

	virtual double getDispersion() const {
		return dispersion;
	}

	virtual void setDispersion(double dispersion) {
		this->dispersion = dispersion;
	}
};

} /* namespace WireScanSets */

#endif /* SCAN_HH_ */

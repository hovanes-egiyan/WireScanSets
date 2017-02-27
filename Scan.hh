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

#include "FunctionOfEmittance.hh"
#include "DerivativeFunctionOfEpsilon.hh"
#include "BoundaryFuncionOfEmmitance.hh"
#include "ScanResult.hh"

namespace WireScanSets {

class Scan: public TNamed {
protected:
	std::map<std::string, ScanResult*> scanMap;

public:
	Scan(const std::string name = "") :
			TNamed(name, name) {
	}
	Scan(const std::string name = "",
			std::map<std::string, ScanResult*>& resultMap ) :
			TNamed(name, name), scanMap() {
		for( auto& scanIter :  resultMap ) {
			auto resultName = scanIter.first;
			auto resultPtr = scanIter.second;
			scanMap[resultName] = new ScanResult( *resultPtr );
		}
	}

	virtual void addResult( ScanResult& result ) {
		scanMap[result.GetName()] = new ScanResult(result);
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
};

} /* namespace WireScanSets */

#endif /* SCAN_HH_ */

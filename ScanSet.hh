/*
 * ScanSet.hh
 *
 *  Created on: Feb 6, 2017
 *      Author: hovanes
 */

#ifndef SCANSET_HH_
#define SCANSET_HH_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "TGraphErrors.h"

#include "BoundaryFunctionOfEmittance.hh"
#include "FunctionOfEmittance.hh"
#include "DerivativeFunctionOfEpsilon.hh"
#include "ScanResult.hh"
#include "Scan.hh"

namespace WireScanSets {

class ScanSet: public TNamed, public FunctionOfEmittance {
public:
	std::vector<ScanResult*> scanList;

	TGraphErrors* graphSigma = 0;
	TGraphErrors* graphSigma2 = 0;

	class fitFuncSigma2: public FunctionOfEmittance {
	public:
		fitFuncSigma2(double epsilon) :
				FunctionOfEmittance(epsilon) {
		}
		fitFuncSigma2(const fitFuncSigma2& obj) :
				FunctionOfEmittance(obj) {
		}
		double operator()(double* x, double* p) {
			double alpha0 = p[0];
			double beta0 = p[1];
			double xVal = x[0];
			double value = 0;
			if (beta0 > 1.0e-25) {
				value = emittance
						* (((1 + alpha0 * alpha0) / (beta0)) * xVal * xVal
								- 2.0 * alpha0 * xVal + beta0);
			}
			return value;
		}
	};

	class dSigma2_dAlpha0: public DerivativeFunctionOfEpsilon {
	public:
		dSigma2_dAlpha0(double epsilon) :
				DerivativeFunctionOfEpsilon(epsilon) {
		}
		dSigma2_dAlpha0(const dSigma2_dAlpha0& obj) :
				DerivativeFunctionOfEpsilon(obj) {
		}
		double operator()(double* x, double* p) {
			double alpha0 = p[0];
			double beta0 = p[1];
			double xVal = x[0];
			double value = 0;
			if (beta0 > 1.0e-25) {
				value =
						emittance
								* (((2.0 * alpha0) / (beta0)) * xVal * xVal
										- 2.0 * xVal);
			}
			return value;
		}
	};

	class dSigma2_dBeta0: public DerivativeFunctionOfEpsilon {
	public:
		dSigma2_dBeta0(double epsilon) :
				DerivativeFunctionOfEpsilon(epsilon) {
		}
		dSigma2_dBeta0(const dSigma2_dBeta0& obj) :
				DerivativeFunctionOfEpsilon(obj) {
		}
		double operator()(double* x, double* p) {
			double alpha0 = p[0];
			double beta0 = p[1];
			double xVal = x[0];
			double value = 0;
			if (beta0 > 1.0e-25) {
				value = emittance
						* (((1 + alpha0 * alpha0) / (beta0 * beta0)) * (-1.0)
								* xVal * xVal + 1.0);
			}
			return value;
		}
	};

	class sigma2_plus_dSigma2: public BoundaryFunctionOfEmittance {
	public:
		sigma2_plus_dSigma2(double epsilon) :
				BoundaryFunctionOfEmittance(epsilon, +1) {
			dFdX1 = new dSigma2_dAlpha0(epsilon);
			dFdX2 = new dSigma2_dBeta0(epsilon);
			meanValue = new fitFuncSigma2(epsilon);
		}
		sigma2_plus_dSigma2(const sigma2_plus_dSigma2& obj) :
				BoundaryFunctionOfEmittance(obj) {
		}
		virtual ~sigma2_plus_dSigma2() {
//            if ( dFdX1 != nullptr ) delete dFdX1;
//            if ( dFdX2 != nullptr ) delete dFdX2;
//            if ( meanValue != nullptr ) delete meanValue;
		}
	};
	class sigma2_minus_dSigma2: public BoundaryFunctionOfEmittance {
	public:
		sigma2_minus_dSigma2(double epsilon) :
				BoundaryFunctionOfEmittance(epsilon, -1) {
			dFdX1 = new dSigma2_dAlpha0(epsilon);
			dFdX2 = new dSigma2_dBeta0(epsilon);
			meanValue = new fitFuncSigma2(epsilon);
		}
		sigma2_minus_dSigma2(const sigma2_minus_dSigma2& obj) :
				BoundaryFunctionOfEmittance(obj) {
		}
		virtual ~sigma2_minus_dSigma2() {
//            if ( dFdX1 != nullptr ) delete dFdX1;
//            if ( dFdX2 != nullptr ) delete dFdX2;
//            if ( meanValue != nullptr ) delete meanValue;
		}
	};

public:
	ScanSet(std::string name = "", double emmitance = 0) :
			TNamed(name.c_str(), name.c_str()), FunctionOfEmittance(emmitance), scanList() {
	}
	ScanSet(std::string name, std::vector<ScanResult*>& scans, double emmitance) :
			TNamed(name.c_str(), name.c_str()), FunctionOfEmittance(emmitance), scanList(
					scans) {
	}
	ScanSet(const ScanSet& set) :
			FunctionOfEmittance(set) {
		*dynamic_cast<TNamed*>(this) = *dynamic_cast<TNamed*>(set.Clone(
				set.GetName()));

		for (auto& oldScan : set.scanList) {
			this->scanList.push_back(new ScanResult(*oldScan));
		}
	}

	ScanSet(std::vector<Scan>& scanVector, std::string dir) :
			FunctionOfEmittance(0) {
		unsigned scanCounter = 0;
		double oldEmittance = 0;
		double oldDispersion = 0;
		// Loops over all the results from the provided map of results
		for (auto& scan : scanVector) {
			// Make sure emittances are the same for the results fo the direction
			std::cout << "Direction is " << dir << " ,  resuts pointer is "
					<< scan.getResult(dir) << std::endl;
			if (scan.getResult(dir) != nullptr) {
				double newEmittance = scan.getResult(dir)->getEmittance();
				if (scanCounter > 0 && newEmittance != oldEmittance) {
					std::string errMsg = "Emittances for " + dir
							+ " in scans are different ";
					throw std::runtime_error(errMsg);
				}
				oldEmittance = newEmittance;
				// Make sure that the dispersions are the same for the results being combined
				double newDispersion = scan.getDispersion();
				if (scanCounter > 0 && newDispersion != oldDispersion) {
					std::string errMsg = "Dispersions  in scans are different ";
					throw std::runtime_error(errMsg);
				}
				oldDispersion = newDispersion;
				// add to the list of the results
				this->scanList.push_back(new ScanResult(*scan.getResult(dir)));
			}
		}
		this->setEmittance(oldEmittance);
	}

	ScanSet(std::map<std::string, Scan*>& scanMap, std::string dir) :
			FunctionOfEmittance(0) {
		std::cout << "Direction is " << dir << std::endl;
		for (auto& scanIt : scanMap) {
			std::cout << "Received Scan key is " << scanIt.first
					<< " Scan pointer is " << scanIt.second << std::endl;
		}

		unsigned scanCounter = 0;
		double oldEmittance = 0;
		double oldDispersion = 0;
		// Loops over all the results from the provided map of results
		for (auto& scanIt : scanMap) {
//    		auto& fileName = scanIt.first;
			auto& scanPtr = scanIt.second;
			// Make sure emittances are the same for the results fo the direction
			std::cout << "Direction is " << dir << " ,  resuts pointer is "
					<< scanPtr->getResult(dir) << std::endl;
			if (scanPtr->getResult(dir) != nullptr) {
				double newEmittance = scanPtr->getResult(dir)->getEmittance();
				if (scanCounter > 0 && newEmittance != oldEmittance) {
					std::string errMsg = "Emittances for " + dir
							+ " in scans are different ";
					throw std::runtime_error(errMsg);
				}
				oldEmittance = newEmittance;
				// Make sure that the dispersions are the same for the results being combined
				double newDispersion = scanPtr->getDispersion();
				if (scanCounter > 0 && newDispersion != oldDispersion) {
					std::string errMsg = "Dispersions  in scans are different ";
					throw std::runtime_error(errMsg);
				}
				oldDispersion = newDispersion;
				// add to the list of the results
				this->scanList.push_back(
						new ScanResult(*scanPtr->getResult(dir)));
			}
		}
		this->setEmittance(oldEmittance);
	}

	virtual ~ScanSet();

	virtual ScanSet& operator=(const ScanSet& set) {
		if (this == &set)
			return *this;
//        *dynamic_cast<TNamed*>( this ) = *dynamic_cast<TNamed*>( set.Clone(
//                ( std::string( "clonOf_" ) + std::string( set.GetName() ) ).c_str() ) );
		*dynamic_cast<TNamed*>(this) = *dynamic_cast<TNamed*>(set.Clone(
				set.GetName()));

		*dynamic_cast<FunctionOfEmittance*>(this) =
				*dynamic_cast<FunctionOfEmittance*>(const_cast<ScanSet*>(&set));

		for (auto& scan : scanList) {
			if (scan != nullptr)
				delete scan;
		}
		scanList.erase(scanList.begin(), scanList.end());

		for (auto& oldScan : set.scanList) {
			this->scanList.push_back(new ScanResult(*oldScan));
		}
		return *this;
	}

	virtual void Print();

	virtual void addScanResults(ScanResult& scan) {
		scanList.push_back(new ScanResult(scan));
	}

	virtual TGraphErrors* makeGraphs();
	virtual TF1* fitGraphs(double xMin, double xMax, Color_t col);

	virtual TF1* getUpperEdge(double xMin, double xMax, Color_t col);
	virtual TF1* getLowerEdge(double xMin, double xMax, Color_t col);

	virtual const std::vector<ScanResult*>& getScanList() const {
		return scanList;
	}

	virtual void setScanList(const std::vector<ScanResult*>& scanMap) {
		this->scanList = scanMap;
	}

	virtual TGraphErrors* getGraphSigma() const {
		return graphSigma;
	}

	virtual TGraphErrors* getGraphSigma2() const {
		return graphSigma2;
	}

};

} /* namespace WireScanSets */

#endif /* SCANSET_HH_ */

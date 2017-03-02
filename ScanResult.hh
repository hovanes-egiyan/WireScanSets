/*
 * ScanResults.hh
 *
 *  Created on: Feb 3, 2017
 *      Author: hovanes
 */

#ifndef SCANRESULT_HH_
#define SCANRESULT_HH_

#include <iostream>
#include <string>
#include <vector>

#include <TNamed.h>

namespace WireScanSets {

class ScanResult: public TNamed {
protected:
	// Location where this result was obtained
	double zLocation = 0;

	// Emittance at which this result was obtained
	double emittance = 0;

	// Sigmas and errors for different wire directions.
	// First is sigma, the second is the error on the sigma.
	std::pair<double, double> sigma = { 0, 0 };

public:
	// DEfault constructor
	ScanResult() :
			TNamed() {
	}
	// Main constructor
	ScanResult(std::string name, double z, double emit, double sigma,
			double deltaSigma) :
			TNamed(name.c_str(), name.c_str()), zLocation(z), emittance(emit), sigma(
					std::pair<double, double>(sigma, deltaSigma)) {
		return;
	}
	// Copy Constructor
	ScanResult(const ScanResult& scan) :
			TNamed() {
		*this = scan;
	}
	// Destructor
	virtual ~ScanResult() {
	}

	// Assignment operator
	virtual ScanResult& operator=(const ScanResult& scan) {
		if (this == &scan)
			return *this;
//		*dynamic_cast<TNamed*>(this) =
//				*dynamic_cast<TNamed*>(scan.Clone(
//						(std::string("clonOf_") + std::string(scan.GetName())).c_str()));
		*dynamic_cast<TNamed*>(this) =
				*dynamic_cast<TNamed*>(scan.Clone( scan.GetName() ) );

		zLocation = scan.zLocation;
		emittance = scan.emittance;
		sigma = scan.sigma;
		return *this;
	}
	// Print info
	virtual void Print() {
		std::cout << "Width for " << this->GetName() << " at location z= "
				<< zLocation << " with emittance= " << emittance << " is "
				<< sigma.first << " +- " << sigma.second << ". " << std::endl;
	}
	// Calculated the pair corresponding to the square of the result by
	// taking the square of the sigma and calculating the appropriate error.
	virtual const std::pair<double, double> getSigma2() const {
		return std::pair<double, double>(sigma.first * sigma.first,
				2. * sigma.first * sigma.second);
	}
	// Getters and Setters
	virtual const std::pair<double, double>& getSigma() const {
		return sigma;
	}

	virtual void setSigma(const std::pair<double, double>& sigma = { 0, 0 }) {
		this->sigma = sigma;
	}

	virtual double getLocation() const {
		return zLocation;
	}

	virtual void setLocation(double location) {
		zLocation = location;
	}

	virtual double getEmittance() const {
		return emittance;
	}

	virtual void setEmittance(double emittance) {
		this->emittance = emittance;
	}
};

} /* namespace WireScanSets */

#endif /* SCANRESULT_HH_ */

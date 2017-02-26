/*
 * DerivativeFunctionOfEpsilon.hh
 *
 *  Created on: Feb 13, 2017
 *      Author: hovanes
 */

#ifndef DERIVATIVEFUNCTIONOFEPSILON_HH_
#define DERIVATIVEFUNCTIONOFEPSILON_HH_

#include "FunctionOfEmittance.hh"

namespace WireScanSets {

class DerivativeFunctionOfEpsilon: public FunctionOfEmittance {
public:
	DerivativeFunctionOfEpsilon(double epsilon) :
			FunctionOfEmittance(epsilon) {
	}
	DerivativeFunctionOfEpsilon(const DerivativeFunctionOfEpsilon& obj) :
			FunctionOfEmittance(obj) {
	}
};

} /* namespace WireScanSets */

#endif /* DERIVATIVEFUNCTIONOFEPSILON_HH_ */

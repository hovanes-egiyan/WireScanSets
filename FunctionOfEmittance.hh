/*
 * FunctionOfEmittance.hh
 *
 *  Created on: Feb 13, 2017
 *      Author: hovanes
 */

#ifndef FUNCTIONOFEMITTANCE_HH_
#define FUNCTIONOFEMITTANCE_HH_

namespace WireScanSets {

class FunctionOfEmittance {
protected:
    double emittance;
public:
    FunctionOfEmittance( double epsilon ) :
            emittance( epsilon ) {
    }
    FunctionOfEmittance( const FunctionOfEmittance& obj ) :
            emittance( obj.emittance ) {
    }
    virtual ~FunctionOfEmittance() {
    }
    virtual double operator()( double* x, double* p ) {
        return 0;
    }

    FunctionOfEmittance& operator=( const FunctionOfEmittance& obj ) {
        if ( this == &obj ) return *this;
        emittance = obj.emittance;
        return *this;
    }
    virtual double getEmittance() const {
        return emittance;
    }
    virtual double setEmittance( double emit ) {
    	return (emittance = emit);
    }
};

} /* namespace WireScanSets */

#endif /* FUNCTIONOFEMITTANCE_HH_ */

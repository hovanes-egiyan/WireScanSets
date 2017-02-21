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
    double emmitance;
public:
    FunctionOfEmittance( double epsilon ) :
            emmitance( epsilon ) {
    }
    FunctionOfEmittance( const FunctionOfEmittance& obj ) :
            emmitance( obj.emmitance ) {
    }
    virtual ~FunctionOfEmittance() {
    }
    virtual double operator()( double* x, double* p ) {
        return 0;
    }

    FunctionOfEmittance& operator=( const FunctionOfEmittance& obj ) {
        if ( this == &obj ) return *this;
        emmitance = obj.emmitance;
        return *this;
    }
    virtual double getEmmitance() const {
        return emmitance;
    }
};

} /* namespace WireScanSets */

#endif /* FUNCTIONOFEMITTANCE_HH_ */

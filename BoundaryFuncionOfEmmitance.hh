/*
 * BoundaryFuncionOfEmmitance.hh
 *
 *  Created on: Feb 13, 2017
 *      Author: hovanes
 */

#ifndef BOUNDARYFUNCIONOFEMMITANCE_HH_
#define BOUNDARYFUNCIONOFEMMITANCE_HH_

#include "FunctionOfEmittance.hh"
#include "DerivativeFunctionOfEpsilon.hh"

namespace WireScanSets {

class BoundaryFuncionOfEmmitance : public FunctionOfEmittance {
protected:
    DerivativeFunctionOfEpsilon* dFdX1 = nullptr;
    DerivativeFunctionOfEpsilon* dFdX2 = nullptr;
    FunctionOfEmittance* meanValue = nullptr;
    double sign = 1.0;

public:
    BoundaryFuncionOfEmmitance( double epsilon, double sgn = 1.0 ) :
            FunctionOfEmittance( epsilon ), dFdX1( nullptr ), dFdX2( nullptr ), meanValue( nullptr ), sign( sgn ) {
    }
    BoundaryFuncionOfEmmitance( const BoundaryFuncionOfEmmitance& obj ) :
            FunctionOfEmittance( obj ) {
        *this = obj;
    }

    virtual ~BoundaryFuncionOfEmmitance() {}

    BoundaryFuncionOfEmmitance& operator=( const BoundaryFuncionOfEmmitance& obj ) {
        if ( this == &obj ) return *this;
        ( *dynamic_cast<FunctionOfEmittance*>( this ) ) =
                *dynamic_cast<FunctionOfEmittance*>( const_cast<BoundaryFuncionOfEmmitance*>( &obj ) );
        dFdX1 = obj.dFdX1;
        dFdX2 = obj.dFdX2;
        meanValue = obj.meanValue;
        sign = obj.sign;
        return *this;
    }

    virtual double operator()( double* x, double* p ) {
        double deltaX1 = p[2];
        double deltaX2 = p[3];
        std::cout << "x= " << x[0] << " deltaX1= " << deltaX1 << " , deltaX2= " <<  deltaX2 << std::endl;
        std::cout << "Mean value= " << ( *meanValue ) ( x, p ) << std::endl;
        std::cout << "Der1= " << ( *dFdX1 )( x, p ) << " , Der2= " << ( *dFdX2 )( x, p ) << std::endl;
        return ( *meanValue ) ( x, p )
                + sign
                        * sqrt(
                                ( *dFdX1 )( x, p ) * ( *dFdX1 )( x, p ) * deltaX1 * deltaX1
                                        + ( *dFdX2 )( x, p ) * ( *dFdX2 )( x, p ) * deltaX2 * deltaX2 );
    }

    const DerivativeFunctionOfEpsilon* getDFdX1() const {
        return dFdX1;
    }

    void setDFdX1( DerivativeFunctionOfEpsilon* fdX1 ) {
        dFdX1 = fdX1;
    }

    const DerivativeFunctionOfEpsilon* getDFdX2() const {
        return dFdX2;
    }

    void setDFdX2( DerivativeFunctionOfEpsilon* fdX2 ) {
        dFdX2 = fdX2;
    }

    const FunctionOfEmittance* getMeanValue() const {
        return meanValue;
    }

    void setMeanValue( FunctionOfEmittance* meanValue ) {
        this->meanValue = meanValue;
    }

    double getSign() const {
        return sign;
    }

    void setSign( double sign ) {
        this->sign = sign;
    }
};

} /* namespace WireScanSets */

#endif /* BOUNDARYFUNCIONOFEMMITANCE_HH_ */
